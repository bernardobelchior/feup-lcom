#include "singleplayer.h"
#include "proj.h"

extern enum singleplayer_controller controller;

void singleplayer_init() {
	if((singleplayer_game.aliens = (alien*) malloc(ALIENS_PER_ROW * ALIEN_ROWS * sizeof(alien))) == NULL)
		return;

	if((singleplayer_game.shields = (shield*) malloc(NUMBER_OF_SHIELDS * sizeof(shield))) == NULL)
		return;

	singleplayer_game.score = 0;

	if( (singleplayer_game.play = player_init()) == NULL)
		return;

	draw_player(singleplayer_game.play);

	wait(3);
}

void singleplayer_tick(){

}

void singleplayer_destruct() {
	free(singleplayer_game.aliens);
	free(singleplayer_game.shields);
}
