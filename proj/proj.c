#include <minix/drivers.h>
#include "events.h"
#include "timer.h"
#include "mouse.h"
#include "keyboard.h"

int start() {
	unsigned long character = 0x00;
	int ipc_status;
	message msg;
	int irq_set_kb = kb_subscribe_int();
	int irq_set_timer = timer_subscribe_int();
	int irq_set_mouse = mouse_subscribe_int();
	int r;
	unsigned char packets[3];
	unsigned short counter = 0;

	mouse_init();

	while (character != ESC_BREAKCODE) { /* You may want to use a different condition */
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kb) { /* keyboard interrupt */
					character = kb_int_handler();
					if (character != KB_2BYTE_SCODE)
						kb_event_handler(word);
				}
				if (msg.NOTIFY_ARG & irq_set_mouse){ /* mouse interrupt */
					mouse_int_handler(j, packet);
					if(packet[0] != MOUSE_ACK && (packet[0] & BIT(3)))
						counter++;
					if(counter == 3){
						counter = 0;
						mouse_event_handler(packet);
					}

				}
				if (msg.NOTIFY_ARG & irq_set_timer){ /* timer interrupt */

				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
		else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	mouse_unsubscribe_int();
	timer_unsuscribe_int();
	kb_unsubscribe_int();
	empty_out_buf();
	return 0;
}

int main(int argc, char **argv) {
	sef_startup();
	start();
	return 0;
}

