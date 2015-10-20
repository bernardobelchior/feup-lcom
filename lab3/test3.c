#include "test3.h"
#include "keyboard.h"

int kbd_test_scan(unsigned short ass) {
	long character = 0x00;
	int ipc_status;
	message msg;
	int irq_set = kb_subscribe_int();
	int r;

	while(character != ESC_BREAKCODE) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					character = kb_int_handler();
					if(!(character == KB_2BYTE_SCODE)){
						if(character & KB_BREAKCODE)
							printf("Key released: %d", character);
						else
							printf("Key pressed: %d", character);
					}
					else{
						if(character & KB_BREAKCODE)
							printf("Key released: %d", character);
						else
							printf("Key pressed: %d", character);
					}
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
}
int kbd_test_leds(unsigned short n, unsigned short *leds) {
	/* To be completed */
}
int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
}

