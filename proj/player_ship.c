#include "player_ship.h"

Player *player_init(unsigned short y, unsigned short x) {

	Player *p1 = (Player *) malloc(sizeof(Player));

	if (p1 == NULL) {
		printf("\tplayer_init(): malloc failed!\n");
		return NULL;
	}

	unsigned char *vmem = vg_get_video_mem();

	p1->numlifes = 3; //TODO implementar dificuldade??
	p1->cannonxpos = 512// metade do ecrã TODO consts simbolicas?
	p1->ypos = 77; // 1/10 do ecra
	//p1->velocity =  TODO ver numlifes
	p1->mempos = vmem+ ypos*768 + cannonxpos;
	return p1;
}

int draw_player(player *p1){
	vg_draw_frame(p1->cannonxpos, p1->ypos, 10, 10, 3);
}

//int move_player; TODO

int player_fire(Player *p1) {
	//CRIAR PROJECTILE TODO
}

void player_hit(Player *p1) {	//TODO

	//faz animacao do jogador atingido

	if (p1->numlifes > 1) {
		p1->numlifes--;
		//volta a desenhar o jogador //TODO
	}

	else {
		player_game_over(p1);
	}
}

int player_game_over (Player *p1){

	free(p1);
	//vai para ecra de gameover; TODO
}
