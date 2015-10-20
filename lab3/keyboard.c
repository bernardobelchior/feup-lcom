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

int kb_unsubscribe_int(void){

	if(sys_irqrmpolicy(&hook_id)!=0)
		return -1;

	if(sys_irqdisable (&hook_id)!=0)
		return -1;

	return 0;
}

long kb_int_handler(void){

	unsigned long stat,word;
	static unsigned long last = 0x00;
	int attempts = 5;
	int i = 0;

	while(i < attempts){
		i++;
		sys_inb(KB_STATUS,&stat);
		if((stat & KB_OUTBUF_FULL) && !(stat & (KB_STAT_PARITY | KB_STAT_TIMEOUT))){
			sys_inb(KB_OUT_BUF, &word);
			if(word == KB_2BYTE_SCODE){
				last=word;
				return word;
			}

			if(last == KB_2BYTE_SCODE){
				word=(last<<4 | word);
				last=0x00;
				return word;
			}

			return word;
		}
		tickdelay(micros_to_ticks(DELAY_US));
	}


}


