#include "singleplayer.h"
#include "proj.h"

extern enum singleplayer_controller controller;
extern enum game_state state;

void singleplayer_init() {
	if(state == main_menu)
		start_menu_destruct();

	if((singleplayer_game.aliens = (alien*) malloc(ALIENS_PER_ROW * ALIEN_ROWS * sizeof(alien))) == NULL)
		return;

	if((singleplayer_game.shields = (shield*) malloc(NUMBER_OF_SHIELDS * sizeof(shield))) == NULL)
		return;

	singleplayer_game.score = 0;

	if( (singleplayer_game.play = player_init()) == NULL)
		return;

	state = singleplayer;
}

void singleplayer_tick(){
	if(controller == mouse)
		player_set_x_pos(singleplayer_game.play, mouse_info.x);
	player_draw(singleplayer_game.play);
}

int singleplayer_move(short x){
	return player_move(singleplayer_game.play, x);
}

int singleplayer_fire(){
	return player_fire(singleplayer_game.play);
}

void singleplayer_destruct() {
	free(singleplayer_game.aliens);
	free(singleplayer_game.shields);
	player_destruct(singleplayer_game.play);
}
