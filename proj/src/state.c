#include "state.h"

void init_state(){
	state = main_menu;
	start_menu_init();
}

void change_state(enum game_state new_state){
	delete_state();

	state = new_state;

	switch(new_state){
	case main_menu:
		start_menu_init();
		break;
	case singleplayer:
		singleplayer_init();
		break;
	case multiplayer:
		versus_mp_game_init();
		break;
	case game_over:
		game_over_menu_init();
		break;
	case highscore:
		highscore_init();
		break;
	case options:
		options_init();
		break;
	}
}

void delete_state(){
	switch(state){
	case main_menu:
		start_menu_destruct();
		break;
	case singleplayer:
		singleplayer_destruct();
		break;
	case multiplayer:
		versus_mp_game_destruct();
		break;
	case game_over:
		game_over_menu_destruct();
		break;
	case highscore:
		highscore_destruct();
		break;
	case options:
		options_destruct();
		break;
	}
}
