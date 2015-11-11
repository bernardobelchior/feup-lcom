#include <minix/syslib.h>
#include <minix/drivers.h>
#include "i8254.h"
#include "timer.h"

unsigned int counter = 0;
int hook_id;

int timer_subscribe_int(void ) {


	hook_id = 10;
	int temp=hook_id;

	if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != 0)
		return -1;

	if(sys_irqenable(&hook_id) != 0)
		return -1;


	return temp;
	return -1;
}

int timer_unsubscribe_int() {

	if(sys_irqrmpolicy(&hook_id) != 0)
		return 1;

	if(sys_irqdisable (&hook_id) !=0)
		return 1;

	return 0;
	return 1;
}

void timer_int_handler() {

	counter++;
	if(counter % 60 == 0){
		printf ("%d segundo(s)\n", counter/60);
	}

}

int timer_test_int(unsigned long time) {

	int ipc_status;
	 message msg;
	 int irq_set = timer_subscribe_int();
	 int r;

	 if(irq_set >= 0)
		 irq_set = BIT(irq_set);
	 else
		 irq_set = 0;

	 while( counter/60 < time ) { /* You may want to use a different condition */
	    /* Get a request message. */
	    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
	        printf("driver_receive failed with: %d", r);
	        continue;
	    }
	    if (is_ipc_notify(ipc_status)) { /* received notification */
	        switch (_ENDPOINT_P(msg.m_source)) {
	            case HARDWARE: /* hardware interrupt notification */
	                if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
	                    timer_int_handler();
	                    /* process it */
	                }
	                break;
	            default:
	                break; /* no other notifications expected: do nothing */
	        }
	    } else { /* received a standard message, not a notification */
	        /* no standard messages expected: do nothing */
	    }
	 }


	return 1;
}
