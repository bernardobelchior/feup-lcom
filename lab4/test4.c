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
						if(packet[0] != MOUSE_ACK && (packet[0] & BIT(3)))
							j++;
						break;
				default:
					break; /* no other notifications expected: do nothing */
					} else { /* received a standard message, not a notification */
						/* no standard messages expected: do nothing */
					}
				}
			}
		}
		printf("B1: %x\tB2: %x\tB3: %x\tLB: %d\tMB: %d\tRB: %d\tXOV: %d\tYOV: %d\t",
				packet[0], packet[1], packet[2], (packet[0] & BIT(0)), (packet[0] & BIT(2)) >> 2, (packet[0] & BIT(1)) >> 1,
				(packet[0] & BIT(6)) >> 6, (packet[0] & BIT(7)) >> 7);
		printf("X: ");
		if(packet[0] & BIT(4))
			printf("%d", ~packet[1]+1);
		else
			printf("%d", packet[1]);
		printf("\tY: ");
		if(packet[0] & BIT(5))
			printf("%d", ~packet[2]+1);
		else
			printf("%d", packet[2]);
		printf("\n");
	}
	mouse_unsubscribe_int();
	empty_out_buf();
	return 0;
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

	if (irq_set_timer >= 0)
		irq_set_timer = BIT(irq_set_timer);
	else
		irq_set_timer = 0;

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
					mouse_int_handler(count, packet);
					if (packet[0] != MOUSE_ACK && (packet[0] & BIT(3))) {
						printf("Byte %d: %x\t", count + 1, packet[count]);
						count++;
						if (count == 3) {
							printf("\n");
							count = 0;
						}
					}
				}
				if (msg.NOTIFY_ARG & irq_set_timer) { /*received timer interrupt*/
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

	return 0;
}

int test_config(void) {
	int irq_set_mouse = mouse_subscribe_int();
	unsigned char packet[3];

	unsigned long stat;

	do{
		write_to_KBC(KBC_STATUS, WRITE_TO_MOUSE);
		write_to_KBC(KBC_OUT_BUF, DISABLE_STRM_MODE);
		read_from_KBC(KBC_IN_BUF, &stat);
	}while(stat != MOUSE_ACK);

	do{
		write_to_KBC(KBC_STATUS, WRITE_TO_MOUSE);
		write_to_KBC(KBC_OUT_BUF, MOUSE_STATUS_REQUEST);
		read_from_KBC(KBC_IN_BUF, &stat);
	}while(stat != MOUSE_ACK);

	unsigned long tmp;
	unsigned int i;
	for(i = 0; i < 3; i++){
		read_from_KBC(KBC_OUT_BUF, &tmp);
		packet[i] = (unsigned char) tmp;
	}

	if(packet[0] & BIT(6))
		printf("Remote mode");
	else
		printf("Stream mode");

	printf("\nData reporting ");
	if(packet[0] & BIT(5))
		printf("enabled");
	else
		printf("disabled");

	printf("\nScaling ");
	if(packet[0] & BIT(4))
		printf("2:1");
	else
		printf("1:1");

	printf("\nLeft mouse button is ");
	if(!(packet[0] & BIT(2)))
		printf("not ");
	printf("being pressed");

	printf("\nMiddle mouse button is ");
	if(!(packet[0] & BIT(1)))
		printf("not ");
	printf("being pressed");

	printf("\nRight mouse button is ");
	if(!(packet[0] & BIT(0)))
		printf("not ");
	printf("being pressed");

	printf("\nResolution: %d", packet[1]);
	printf("\nSample rate: %d\n", packet[2]);

	printf("Bytes: %x\t%x\t%x\n", packet[0], packet[1], packet[2]);

	mouse_unsubscribe_int();
	empty_out_buf();
	return 0;
}

int test_gesture(short length, unsigned short tolerance) {

	int irq_set_mouse = mouse_subscribe_int();
	int r;
	int ipc_status;
	unsigned int count = 0;
	message msg;
	unsigned char packet[3];
	int length_sum=0;
	int tolerance_sum=0;

	if (irq_set_mouse >= 0)
		irq_set_mouse = BIT(irq_set_mouse);
	else
		irq_set_mouse = 0;

	while (1) {
		/* Get a request message. */
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_mouse) { /* subscribed interrupt */
					mouse_int_handler(count, packet);
					if (packet[0] != MOUSE_ACK && (packet[0] & BIT(3))) {
						printf("Byte %d: %x\t", count + 1, packet[count]);
						count++;
						if (count == 3) { /*finished packet*/

							printf("\n");
							count = 0;

							if (packet[0] & BIT(1)) { /*right button was pressed  -- goes to drawing state*/
								if(packet[0] & BIT(4)){
									tolerance_sum-= 256 - packet[1]; printf("\n\n%d\n\n",256 - packet[1]);}
								else
									tolerance_sum+= packet[1];

								if(tolerance_sum > tolerance || (-1 * tolerance_sum) > tolerance){
									length_sum=0; 		//the movement exceeded the tolerance
									tolerance_sum=0;	//resets values

									break;
								}

								if(packet[0] & BIT(5)){
									length_sum -= 256 - packet[2];
								}
								else
									length_sum += packet[2]; // sums the length


								if((length_sum >= length && length > 0) || (length_sum <= length && length < 0)){
									mouse_unsubscribe_int();
									empty_out_buf();
									return 0;
								}
							}
							else {
								length_sum = 0;
								tolerance_sum=0;
							}
						}
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
	mouse_unsubscribe_int();
	empty_out_buf();
	return 1;
}
