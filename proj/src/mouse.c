#include <minix/syslib.h>
#include <minix/drivers.h>
#include "mouse.h"
#include "video_gr.h"
#include "timer.h"

extern mouse_info_t mouse_info;
unsigned int time = 0;
int hook_id;

int write_to_KBC(char destination, unsigned long information){
	unsigned long status;
	sys_inb(KBC_STATUS, &status);

	if(!(status & (KBC_INBUF_FULL | KBC_STAT_PARITY | KBC_STAT_TIMEOUT))){
		unsigned long i = 0;
		sys_outb(destination, information);
		return 1;
	}

	return 0;
}

int read_from_KBC(char origin, unsigned long* information){
	unsigned long status;
	sys_inb(KBC_STATUS, &status);

	if(!(status & (!KBC_OUTBUF_FULL | KBC_STAT_PARITY | KBC_STAT_TIMEOUT))){
		sys_inb(origin, information);
		return 1;
	}

	return 0;
}

int mouse_subscribe_int(void) {

	hook_id = 20;
	int temp;

	if(hook_id >= 0)
			temp = BIT(hook_id);
		else
			temp = 0;

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0)
		return -1;

	if (sys_irqenable(&hook_id) != 0)
		return -1;

	unsigned long stat;
	do{
		write_to_KBC(KBC_COMMAND, KBC_ENABLE_MOUSE);
		write_to_KBC(KBC_COMMAND, WRITE_TO_MOUSE);
		write_to_KBC(KBC_OUT_BUF, ENABLE_DATA_PACKETS);
		read_from_KBC(KBC_IN_BUF, &stat);
	} while (stat != MOUSE_ACK);

	return temp;
}

int mouse_unsubscribe_int(void) {

	if (sys_irqrmpolicy(&hook_id) != 0)
		return -1;

	if (sys_irqdisable(&hook_id) != 0)
		return -1;

	return 0;
}

void mouse_int_handler(int counter, char packets[]){
	unsigned long info;
	read_from_KBC(KBC_OUT_BUF, &info);

	packets[counter] = (char) info;
}

void empty_out_buf(void){
	unsigned long status;
	sys_inb(KBC_STATUS, &status);
	while(status & KBC_OUTBUF_FULL){
		unsigned long tmp;
		sys_inb(KBC_OUT_BUF, &tmp);
		sys_inb(KBC_STATUS, &status);
	}
}

void mouse_init(){
	mouse_info.x = get_h_res()/2;
	mouse_info.y = get_v_res()/2;
	mouse_info.rmb_pressed = 0;
	mouse_info.mmb_pressed = 0;
	mouse_info.lmb_pressed = 0;
}

void mouse_draw(){
	vg_draw_frame(mouse_info.x, mouse_info.y, 5, 5, rgb(0xFF66B2));
}
