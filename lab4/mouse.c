#include "mouse.h"


int hook_id;

int kb_subscribe_int(void) {

	hook_id = 20;
	int temp = hook_id;
	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0)
		return -1;

	if (sys_irqenable(&hook_id) != 0)
		return -1;

	return temp;
}

int kb_unsubscribe_int(void) {

	if (sys_irqrmpolicy(&hook_id) != 0)
		return -1;

	if (sys_irqdisable(&hook_id) != 0)
		return -1;

	return 0;
}

int write_to_KBC(char destination, char information){


}

void mouse_int_handler(int counter, char packets[]){

}
