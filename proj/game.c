#include "game.h"

void game_init(){
	singleplayer.aliens = (Alien*) malloc(ALIENS_PER_ROW*ALIEN_ROWS*sizeof(Alien));
	singleplayer.shields = (Shield*) malloc(NUMBER_OF_SHIELDS*sizeof(Shield));
}


void game_destruct(){
	free(singleplayer.aliens);
	free(singleplayer.shields);
}
