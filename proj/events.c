#include "events.h"
#include "keyboard.h"
#include "mouse.h"

static mouse_info mouse;
static game_state state;


unsigned short get_h_res(){ //temporary
	return 1024;
}

unsigned short get_v_res(){ //temporary
	return 768;
}

void game_init(){
	state = main_menu;
	mouse_init();
}

void mouse_init(){
	mouse.x = get_h_res()/2; //H_RES/2
	mouse.y = get_v_res()/2; //Y_RES/2
	mouse.rmb_pressed = 0;
	mouse.mmb_pressed = 0;
	mouse.lmb_pressed = 0;
}

void kb_event_handler(unsigned short key){
	if (key & KB_BREAKCODE)
		key_released(key);
	else
		key_pressed(key);
}

void mouse_event_handler(unsigned char packet[3]){

	//Middle mouse button pressed/released

	if(!(packet[0] & MOUSE_MB_PRESSED) && mouse.mmb_pressed){
		mouse.mmb_pressed = 0;
		mmb_released();
	}
	else if((packet[0] & MOUSE_MB_PRESSED) && !mouse.mmb_pressed){
		mouse.mmb_pressed = 1;
		mmb_pressed();
	}

	//Right mouse button pressed/released

	if(!(packet[0] & MOUSE_RB_PRESSED) && mouse.rmb_pressed){
		mouse.rmb_pressed = 0;
		rmb_released();
	}
	else if((packet[0] & MOUSE_RB_PRESSED) && !mouse.rmb_pressed){
		mouse.rmb_pressed = 1;
		rmb_pressed();
	}

	//Left mouse button pressed/released

	if(!(packet[0] & MOUSE_LB_PRESSED) && mouse.lmb_pressed){
		mouse.lmb_pressed = 0;
		lmb_released();
	}
	else if((packet[0] & MOUSE_LB_PRESSED) && !mouse.lmb_pressed){
		mouse.lmb_pressed = 1;
		lmb_pressed();
	}

	//Update mouse x position

	if(packet[0] & MOUSE_X_SIGNED){
		short xdelta = 0xFF00 | packet[1];
		mouse.x += xdelta;
		if(mouse.x < 0)
			mouse.x = 0;
	}
	else{
		mouse.x += packet[1];
		if(mouse.x > get_h_res())
			mouse.x = get_h_res();
	}

	//Update mouse y position

	if(packet[0] & MOUSE_Y_SIGNED){
		short ydelta = 0xFF00 | packet[2];
		mouse.y -= ydelta;
		if(mouse.y > get_v_res())
			mouse.y = get_v_res();
	}
	else{
		mouse.y -= packet[2];
		if(mouse.y < 0)
			mouse.y = 0;
	}

	//printf("Mouse position: (%d, %d)\n", mouse.x, mouse.y);
}

void key_pressed(unsigned long key){
	//printf("Key pressed: 0x%x\n", key);
}

void key_released(unsigned long key){
	//printf("Key released: 0x%x\n", key);
}

void mmb_released(){
	//printf("Middle mouse button released.\n");
}

void mmb_pressed(){
	//printf("Middle mouse button pressed.\n");
}

void rmb_released(){
	//printf("Right mouse button released.\n");
}

void rmb_pressed(){
	//printf("Right mouse button pressed.\n");
}

void lmb_released(){
	//printf("Left mouse button released.\n");
}

void lmb_pressed(){
	//printf("Left mouse button pressed.\n");
}

void tick(){
	//printf("Tick.\n");
}

