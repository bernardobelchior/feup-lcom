#include "singleplayer.h"
#include "proj.h"

extern enum singleplayer_controller controller;

void singleplayer_init() {
	singleplayer_game.aliens = (alien*) malloc(ALIENS_PER_ROW * ALIEN_ROWS * sizeof(alien));
	singleplayer_game.shields = (shield*) malloc(NUMBER_OF_SHIELDS * sizeof(shield));
}

void singleplayer_tick(){

}

void singleplayer_destruct() {
	free(singleplayer_game.aliens);
	free(singleplayer_game.shields);
}
