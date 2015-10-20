#include <minix/syslib.h>
#include <minix/drivers.h>
#include "keyboard.h"

int hook_id;

int kb_subscribe_int(void){

	hook_id=4;
	int temp = hook_id;
	if(sys_irqsetpolicy(KB_IRQ,IRQ_REENABLE|IRQ_EXCLUSIVE,&hook_id)!=0)
		return -1;

	if(sys_irqenable(&hook_id)!=0)
		return -1;

	return temp;
}

