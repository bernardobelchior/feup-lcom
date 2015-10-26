#include "test3.h"
#include "keyboard.h"
#include "timer.h"

int kbd_test_scan(unsigned short ass) {
	long character = 0x00;
	int ipc_status;
	message msg;
	int irq_set = kb_subscribe_int();
	int r;

	while (character != ESC_BREAKCODE) { /* You may want to use a different condition */
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				//if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
				character = kb_int_handler();
				if (character & KB_BREAKCODE)
					printf("Key released: %d\n", character);
				else
					printf("Key pressed: %d\n", character);
				//}
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
	unsigned short j = n;
	int irq_set = timer_subscribe_int();
	int r, ipc_status;
	message msg;

	 if(irq_set >= 0)
		 irq_set = BIT(irq_set);
	 else
		irq_set = 0;

	while (j > 0) {
		printf("j = %d\n",j);
		if (r = driver_receive(ANY, &msg, &ipc_status)) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					timer_int_handler_leds(&j,leds[j]);
					/* process it */
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
		else{/*received a standard message, not a notification*/
			/*no standard messages expected, do nothing*/
		}
	}
}
int kbd_test_timed_scan(unsigned short n) {
	/* To be completed */
}

