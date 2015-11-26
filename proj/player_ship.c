#include "player_ship.h"

player* player_init() {

	player *p1 = (player *) malloc(sizeof(player));

	if (p1 == NULL) {
		printf("\tplayer_init(): malloc failed!\n");
		return NULL;
	}

	//unsigned char *vmem = vg_get_double_buffer();

	p1->num_lives = NUM_LIVES; //TODO implementar dificuldade??
	p1->cannonxpos = PLAYER_INITIAL_X_POS;
	p1->ypos = PLAYER_INITIAL_Y_POS;
	//p1->velocity =
	//TODO ver numlifes
	//p1->mem_pos = vmem+ p1->ypos*768 + p1->cannonxpos;

	return p1;
}

int player_draw(player *p1){
	vg_draw_frame(p1->cannonxpos, p1->ypos, SHIP_WIDTH, SHIP_HEIGHT, 3);
}

int player_fire(player *p1) {
	//CRIAR PROJECTILE TODO
}

void player_hit(player *p1) {	//TODO

	//faz animacao do jogador atingido

	if (p1->num_lives > 1) {
		p1->num_lives--;
		//volta a desenhar o jogador //TODO
	}

	else {
		player_game_over(p1);
	}
}

int player_move(player *p1, short x){
	if(p1->cannonxpos + x < 0){
		p1->cannonxpos = 0;
		return 1;
	}

	if(p1->cannonxpos + x + SHIP_WIDTH >= 1024){
		p1->cannonxpos = 1024 - SHIP_WIDTH;
		return 1;
	}

	p1->cannonxpos += x;
	return 0;
}

int player_set_x_pos(player *p1, unsigned short x){
	if(x + SHIP_WIDTH >= 1024){
		p1->cannonxpos = 1024 - SHIP_WIDTH;
		return 1;
	}

	if(x < 0){
		p1->cannonxpos = 0;
		return 1;
	}

	p1->cannonxpos = x;
	return 0;
}

int player_game_over (player *p1){
	//vai para ecra de gameover; TODO
	player_destruct(p1);
	return 0;
}

void player_destruct(player *p1){
	free(p1);
}
