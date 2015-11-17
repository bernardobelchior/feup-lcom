#include "events.h"
#include "keyboard.h"
#include "mouse.h"

static mouse_info mouse;

void mouse_init(){
	mouse.x = 0; //H_RES/2
	mouse.y = 0; //Y_RES/2
	mouse.rmb_pressed = 0;
	mouse.mmb_pressed = 0;
	mouse.lmb_pressed = 0;
}

void kb_event_handler(unsigned long key){
	if (key & KB_BREAKCODE)
		key_released(word);
	else
		key_pressed(word);
}


void mouse_event_handler(unsigned char packet[3]){

}


void kb_key_pressed(unsigned long key){

}

void kb_key_released(unsigned long key){

}

