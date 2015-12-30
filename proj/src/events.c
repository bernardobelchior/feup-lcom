#include "events.h"

extern mouse_info_t mouse_info;
extern enum game_state state;
extern enum singleplayer_controller controller;
extern menu* start_menu;
extern menu* highscore_menu;
extern menu* options_menu;
extern menu* game_over_menu;

void kb_event_handler(unsigned short key) {
	if (key & KB_BREAKCODE)
		key_released(key);
	else
		key_pressed(key);
}

void mouse_event_handler(unsigned char packet[3]) {
	//Middle mouse button pressed/released

	if (!(packet[0] & MOUSE_MB_PRESSED) && mouse_info.mmb_pressed) {
		mouse_info.mmb_pressed = 0;
		mmb_released();
	} else if ((packet[0] & MOUSE_MB_PRESSED) && !mouse_info.mmb_pressed) {
		mouse_info.mmb_pressed = 1;
		mmb_pressed();
	}

	//Right mouse button pressed/released

	if (!(packet[0] & MOUSE_RB_PRESSED) && mouse_info.rmb_pressed) {
		mouse_info.rmb_pressed = 0;
		rmb_released();
	} else if ((packet[0] & MOUSE_RB_PRESSED) && !mouse_info.rmb_pressed) {
		mouse_info.rmb_pressed = 1;
		rmb_pressed();
	}

	//Left mouse button pressed/released

	if (!(packet[0] & MOUSE_LB_PRESSED) && mouse_info.lmb_pressed) {
		mouse_info.lmb_pressed = 0;
		lmb_released();
	} else if ((packet[0] & MOUSE_LB_PRESSED) && !mouse_info.lmb_pressed) {
		mouse_info.lmb_pressed = 1;
		lmb_pressed();
	}

	//Update mouse x position

	if (packet[0] & MOUSE_X_SIGNED) {
		short xdelta = 0xFF00 | packet[1];
		mouse_info.x += xdelta;
		if (mouse_info.x < 0)
			mouse_info.x = 0;
	} else {
		mouse_info.x += packet[1];
		if (mouse_info.x > get_h_res())
			mouse_info.x = get_h_res();
	}

	//Update mouse y position

	if (packet[0] & MOUSE_Y_SIGNED) {
		short ydelta = 0xFF00 | packet[2];
		mouse_info.y -= ydelta;
		if (mouse_info.y > get_v_res())
			mouse_info.y = get_v_res();
	} else {
		mouse_info.y -= packet[2];
		if (mouse_info.y < 0)
			mouse_info.y = 0;
	}
}

void key_pressed(unsigned long key) {
	switch (state) {
	case main_menu: {
		switch (key) {
		case UP_ARROW_MAKECODE:
			previous_button(start_menu);
			break;
		case DOWN_ARROW_MAKECODE:
			next_button(start_menu);
			break;
		case ENTER_MAKECODE:
			press_selected_button(start_menu);
			break;
		case ESC_MAKECODE:
			cancel_button(start_menu);
			break;
		}
		break;
	}
	case singleplayer:
		switch (key) {
		case ESC_MAKECODE: //TODO add a pause menu
			singleplayer_game_over();
			break;
		case RIGHT_ARROW_MAKECODE:
			if(controller == keyboard)
				singleplayer_move(1);
			break;
		case LEFT_ARROW_MAKECODE:
			if(controller == keyboard)
				singleplayer_move(-1);
			break;
		case SPACE_MAKECODE:
			if(controller == keyboard)
				singleplayer_fire();
			break;
		}
		break;
		case multiplayer:
			switch(key){
			case A_MAKECODE:
				versus_mp_move(1,-1);
				break;

			case D_MAKECODE:
				versus_mp_move(1,1);
				break;

			case W_MAKECODE:
				versus_mp_fire(1);
				break;

			case LEFT_ARROW_MAKECODE:
				versus_mp_move(2,-1);
				break;

			case RIGHT_ARROW_MAKECODE:
				versus_mp_move(2,1);
				break;

			case UP_ARROW_MAKECODE:
				versus_mp_fire(2);
				break;

			case ESC_MAKECODE:
				change_state(main_menu);
				break;
			}
			break;
		case highscore:

			break;
		case options:

			break;
	}
}

void key_released(unsigned long key) {
	switch (state) {
	case main_menu:

		break;
	case singleplayer:

		break;
	case multiplayer:

		break;
	case highscore:

		break;
	case options:

		break;
	}
}

void mmb_released() {
	//printf("Middle mouse button released.\n");
}

void mmb_pressed() {
	//printf("Middle mouse button pressed.\n");
}

void rmb_released() {
	//printf("Right mouse button released.\n");
}

void rmb_pressed() {
	//printf("Right mouse button pressed.\n");
}

void lmb_released() {
	//printf("Left mouse button released.\n");
	switch(state){
	case main_menu:
		click_button(start_menu, mouse_info.x, mouse_info.y);
		break;
	case highscore:
		click_button(highscore_menu, mouse_info.x, mouse_info.y);
		break;
	case options:
		click_button(options_menu, mouse_info.x, mouse_info.y);
		break;
	case game_over:
		click_button(game_over_menu, mouse_info.x, mouse_info.y);
		break;
	}
}

void lmb_pressed() {
	if(state == singleplayer && controller == mouse)
		singleplayer_fire(); //TODO if the player is still pressing the lmb, the ship must fire at a fixed rate
	//printf("Left mouse button pressed.\n");
}

void tick() {
	switch (state) {
	case main_menu:
		start_menu_draw();
		break;
	case singleplayer:
		singleplayer_tick();
		break;
	case multiplayer:
		versus_mp_game_tick();
		break;
	case highscore:
		highscore_tick();
		mouse_draw();
		break;
	case game_over:
		game_over_menu_tick();
		mouse_draw();
		break;
	case options:
		options_tick();
		mouse_draw();
		break;
	}
	vg_update_screen();
	//printf("Tick.\n");
}
