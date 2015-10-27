#include "test3.h"
#include "keyboard.h"
#include "timer.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#define LED_RESET -1

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
				if(ass == 0)
					character = kb_int_handler();
				else {
					sys_enable_iop(SELF);
					funcasm();
				}
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

	kb_toggle_led(LED_RESET); //toggles off the 3 leds

	unsigned short j = 0;
	int irq_set = timer_subscribe_int();
	int r, ipc_status;
	message msg;

	if (irq_set >= 0)
		irq_set = BIT(irq_set);
	else
		irq_set = 0;

	while (j < n) {
		if (r = driver_receive(ANY, &msg, &ipc_status)) {
			printf("driver_receive failed with: %d", r);
			continue;
		}

		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					timer_int_handler_leds(&j, leds[j]);
					/* process it */
				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {/*received a standard message, not a notification*/
			/*no standard messages expected, do nothing*/
		}
	}
}
int kbd_test_timed_scan(unsigned short n) {

	unsigned short time = 0;
	int irq_set_timer = timer_subscribe_int();
	int irq_set_kb = kb_subscribe_int();
	printf("irq set kb = %d\n\n", irq_set_kb);
	int r, ipc_status;
	message msg;
	long character = 0x00;

	if (irq_set_timer >= 0)
		irq_set_timer = BIT(irq_set_timer);
	else
		irq_set_timer = 0;

	if(irq_set_kb >= 0)
		irq_set_kb = BIT(irq_set_kb);
	else
		irq_set_kb = 0;

	while (character != ESC_BREAKCODE && time != n) {
		if (r = driver_receive(ANY, &msg, &ipc_status)) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				if (msg.NOTIFY_ARG & irq_set_timer) { /* subscribed interrupt */
					timed_scan_int_handler(&time);
				}

				if (msg.NOTIFY_ARG & irq_set_kb) {
					time = 0;
					character = kb_int_handler();
					if (character & KB_BREAKCODE)
						printf("Key released: %d\n", character);
					else
						printf("Key pressed: %d\n", character);
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {/*received a standard message, not a notification*/
			/*no standard messages expected, do nothing*/
		}

	}
}

