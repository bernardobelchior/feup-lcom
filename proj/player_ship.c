#include "player_ship.h"

player* player_init() {

	player *p1 = (player *) malloc(sizeof(player));

	if (p1 == NULL) {
		printf("\tplayer_init(): malloc failed!\n");
		return NULL;
	}

	//unsigned char *vmem = vg_get_video_mem();

	p1->num_lives = NUM_LIVES; //TODO implementar dificuldade??
	p1->cannonxpos = INITIAL_CANNON_POS;// metade do ecra TODO consts simbolicas?
	p1->ypos = INITIAL_SHIP_POS; // 9/10 do ecra
	//p1->velocity =  TODO ver numlifes
	//p1->mem_pos = vmem+ p1->ypos*768 + p1->cannonxpos;

	return p1;
}

int draw_player(player *p1){
	vg_draw_frame(p1->cannonxpos, p1->ypos, 10, 10, 3);
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

int move_player(player *p1, short x){
	if(p1->cannonxpos + x < 0){
		p1->cannonxpos = 0;
		return 1;
	}

	if(p1->cannonxpos + x >= 1024){ //TODO cannonxpos + x + width
		p1->cannonxpos = 1023;
		return 1;
	}

	p1->cannonxpos += x;
	return 0;
}

int player_game_over (player *p1){

	free(p1);
	//vai para ecra de gameover; TODO
}
