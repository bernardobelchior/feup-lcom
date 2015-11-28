#include "player_ship.h"

player* player_init() {

	player *p1 = (player *) malloc(sizeof(player));

	if (p1 == NULL) {
		printf("\tplayer_init(): malloc failed!\n");
		return NULL;
	}

	//unsigned char *vmem = vg_get_double_buffer();

	p1->num_lives = NUM_LIVES; //TODO implementar dificuldade??
	p1->x = PLAYER_INITIAL_X_POS;
	p1->y = PLAYER_INITIAL_Y_POS;
	//p1->velocity =
	//TODO ver numlifes
	//p1->mem_pos = vmem+ p1->ypos*768 + p1->cannonxpos;

	return p1;
}

int player_draw(player *p1){
	vg_draw_frame(p1->x, p1->y, SHIP_WIDTH, SHIP_HEIGHT, 3);
}

projectile *player_fire(player *p1) {
	return projectile_init((int) (p1->x+SHIP_WIDTH/2), p1->y-1, -5);
}

void player_hit(player *p1) {	//TODO

	//faz animacao do jogador atingido

	if (p1->num_lives > 1) {
		p1->num_lives--;
		p1->x = PLAYER_INITIAL_X_POS;
		p1->y = PLAYER_INITIAL_Y_POS;
	} else
		player_game_over(p1);
}

int player_move(player *p1, char direction){
	if(p1->x + direction*SHIP_X_DELTA < 0){
		p1->x = 0;
		return 1;
	}

	if(p1->x + direction*SHIP_X_DELTA + SHIP_WIDTH >= 800){
		p1->x = 800 - SHIP_WIDTH;
		return 1;
	}

	p1->x += direction*SHIP_X_DELTA;
	return 0;
}

int player_set_x_pos(player *p1, unsigned short x){
	if(x + SHIP_WIDTH >= 800){
		p1->x = 800 - SHIP_WIDTH;
		return 1;
	}

	if(x < 0){
		p1->x = 0;
		return 1;
	}

	p1->x = x;
	return 0;
}

int player_check_collision(player* p1, unsigned short x, unsigned short y){//TODO make a better check because an object can collide with another, even thought his x,y position doesnt
	return ((x > p1->x && x < p1->x + SHIP_WIDTH) && (y > p1->y && y < p1->y + SHIP_HEIGHT));
}

int player_game_over (player *p1){
	//vai para ecra de gameover; TODO
	player_destruct(p1);
	return 0;
}

void player_destruct(player *p1){
	free(p1);
}
