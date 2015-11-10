#include "timer.h"
#include "test4.h"
#include "i8254.h"
#include "i8042.h"
#include <minix/syslib.h>
#include <minix/drivers.h>

int test_packet(unsigned short cnt) {
	int irq_set_mouse = mouse_subscribe_int();
	int r;
	int ipc_status;
	unsigned char packet[3];
	message msg;

	unsigned long stat;
	do {
		write_to_KBC(KBC_STATUS, WRITE_TO_MOUSE);
		write_to_KBC(KBC_OUT_BUF, SET_STREAM_MODE);
		read_from_KBC(KBC_IN_BUF, &stat);
	} while (stat != MOUSE_ACK);

	if (irq_set_mouse >= 0)
		irq_set_mouse = BIT(irq_set_mouse);
	else
		irq_set_mouse = 0;

	unsigned int i;
	for (i = 0; i < cnt; i++) {
		unsigned int j = 0;
		while (j < 3) {
			/* Get a request message. */
			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */
					if (msg.NOTIFY_ARG & irq_set_mouse) { /* subscribed interrupt */
						mouse_int_handler(j, packet);
						if(packet[0] != MOUSE_ACK && (packet[0] & BIT(3))){
							printf("Byte %d: %x\t", j + 1, packet[j]);
							j++;
						}
						break;
				default:
					break; /* no other notifications expected: do nothing */
					} else { /* received a standard message, not a notification */
						/* no standard messages expected: do nothing */
					}
				}
			}
		}
		printf("\n");
	}
	mouse_unsubscribe_int();
	empty_out_buf();
}

int test_async(unsigned short idle_time) {
	int irq_set_mouse = mouse_subscribe_int();
	int irq_set_timer = timer_subscribe_int();
	int r;
	int ipc_status;
	unsigned short time = 0;
	unsigned int count = 0;

	unsigned char packet[3];
	message msg;

	if (irq_set_mouse >= 0)
		irq_set_mouse = BIT(irq_set_mouse);
	else
		irq_set_mouse = 0;

	while (time < idle_time) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_mouse) { /* subscribed interrupt */
					time = 0;
					count++;
					mouse_int_handler(count, packet);
					printf("Byte %d: %x\t", count, packet[count - 1]);
					if (count == 3) {
						printf("\n");
						count = 0;
					}
				}
				if (msg.NOTIFY_ARG & irq_set_timer) {
					timed_scan_int_handler(&time);
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	mouse_unsubscribe_int();
	empty_out_buf();
}

int test_config(void) {
	unsigned char packet[3];
	char ack;
	int error = 0;
	while (error) {
		error = 0;
		write_to_KBC(KBC_COMMAND, WRITE_TO_MOUSE);
		write_to_KBC(KBC_OUT_BUF, MOUSE_STATUS_REQUEST);
		unsigned int i;
		for (i = 0; i < 3; i++) {
			unsigned long tmp;
			read_from_KBC(KBC_IN_BUF, &tmp);
			ack = (char) tmp;
			if (ack != MOUSE_ACK) {
				error = 1;
				break;
			} else {
				read_from_KBC(KBC_OUT_BUF, &tmp);
				packet[i] = (char) tmp;
				printf("Byte %d: %x\t", i, packet[i]);
			}
		}
	}
}

int test_gesture(short length, unsigned short tolerance) {

}
