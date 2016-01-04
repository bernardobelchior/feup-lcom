#include "player.h"
#include "state.h"
#include "bitmap.h"

player* player_init(enum player_type mode) {
	player *p1 = (player *) malloc(sizeof(player));

	if (p1 == NULL) {
		printf("\tplayer_init(): malloc failed!\n");
		return NULL;
	}

	p1->num_lives = NUM_LIVES; //TODO implementar dificuldade??

#ifdef DEBUG
	p1->num_lives = 1;
#endif

	switch(mode) {
	case SP:
		p1->player_ship = (bitmap*) bitmap_load(SHIP_RES_NAME);
		p1->y = SP_PLAYER_INITIAL_Y_POS;
		break;
	case MP1:
		p1->player_ship = (bitmap*) bitmap_load(INV_SHIP_RES_NAME);
		p1->y = MP_PLAYER_1_INITIAL_Y_POS;
		break;
	case MP2:
		p1->player_ship = (bitmap*) bitmap_load(SHIP_RES_NAME);
		p1->y = MP_PLAYER_2_INITIAL_Y_POS;
		break;
	}
	p1->x = PLAYER_INITIAL_X_POS;
	p1->score = 0;
	p1->initial_y = p1->y;
	p1->life = (bitmap*) bitmap_load("life.bmp");
	p1->state = PLAYER_ALIVE;
	p1->destroy = (bitmap*) bitmap_load("ship_destroyed.bmp");
	p1->ticks = 0;
	p1->ticks_since_last_fire = 0;
	return p1;
}

int player_draw(player *p1){
	if(p1->state == PLAYER_ALIVE){
		bitmap_draw(p1->player_ship, p1->x, p1->y, ALIGN_LEFT);
	} else {
		bitmap_draw(p1->destroy, p1->x, p1->y, ALIGN_LEFT);
	}
}

int player_fire(player *p1, char direction) {
	if(p1->state == PLAYER_DESTROYED)
		return 1;

	if(p1->ticks_since_last_fire > TICKS_BETWEEN_SHOTS)
		p1->ticks_since_last_fire = 0;
	else
		return 1;

	if(direction == 1){
		return projectile_init(p1, (unsigned short) (p1->x+SHIP_WIDTH/2),
				p1->y-PROJECTILE_HEIGHT-1, -1 * PLAYER_PROJECTILE_VELOCITY);
	}
	else {
		return projectile_init(p1, (unsigned short) (p1->x+SHIP_WIDTH/2),
				p1->y+SHIP_HEIGHT+PROJECTILE_HEIGHT+1, PLAYER_PROJECTILE_VELOCITY);
	}
}

void player_tick(player* p1){
	if(p1->state == PLAYER_DESTROYED){
		if(p1->ticks > 60){
			p1->x = PLAYER_INITIAL_X_POS;
			p1->y = p1->initial_y;
			p1->state = PLAYER_ALIVE;
		}
	}

	p1->ticks_since_last_fire++;
	p1->ticks++;
	player_draw(p1);
}

int player_hit(player *p1) {
	if (p1->num_lives > 0) {
		p1->num_lives--;
		p1->ticks = 0;
		p1->state = PLAYER_DESTROYED;
		return 0;
	} else
		return 1;
}

int player_move(player *p1, char direction){
	if(p1->state == PLAYER_DESTROYED)
		return 1;

	if(p1->x + direction*SHIP_X_DELTA < 0)
		p1->x = 0;

	if(p1->x + direction*SHIP_X_DELTA + SHIP_WIDTH >= get_h_res())
		p1->x = get_h_res() - SHIP_WIDTH - 1;

	p1->x += direction*SHIP_X_DELTA;
	return 0;
}

int player_set_x_pos(player *p1, unsigned short x){
	if(p1->state == PLAYER_DESTROYED)
		return 1;

	if(x + SHIP_WIDTH >= get_h_res()){
		p1->x = get_h_res() - SHIP_WIDTH;
		return 1;
	}

	if(x < 0){
		p1->x = 0;
		return 1;
	}

	p1->x = x;
	return 0;
}

int player_set_y_pos(player *p1, unsigned short y){

	if(p1 == NULL || y < 0 || y > get_v_res())
		return 1;

	p1->y = y;

	return 0;
}

int player_collision_handler(player* p1, struct _projectile* proj){
	if(p1->state == PLAYER_DESTROYED)
		return 0;

	if((proj->x > p1->x && proj->x < p1->x + SHIP_WIDTH) && (proj->y > p1->y && proj->y < p1->y + SHIP_HEIGHT)
			|| (proj->x + proj->width > p1->x && proj->x + proj->width < p1->x + SHIP_WIDTH) && (proj->y + proj->height > p1->y && proj->y + proj->height < p1->y + SHIP_HEIGHT)){
		player_hit(p1);

		if(proj->shooter != NULL)
			proj->shooter->score++;

		return 1;
	}
	return 0;
}

void player_mirror_image(player* p1){
	bitmap_mirror_horizontally(p1->player_ship);
}

void player_destruct(player *p1){
	if(p1 == NULL)
		return;

	bitmap_delete(p1->life);

	//bitmap_delete(p1->player_ship); //crashes here
	//free(p1); //crashes here
}
