#include "player.h"
#include "state.h"
#include "bitmap.h"

player* player_init() {

	player *p1 = (player *) malloc(sizeof(player));

	if (p1 == NULL) {
		printf("\tplayer_init(): malloc failed!\n");
		return NULL;
	}

	p1->player_ship = (bitmap*) bitmap_load(SHIP_RES_NAME);

	p1->num_lives = NUM_LIVES; //TODO implementar dificuldade??
	p1->x = PLAYER_INITIAL_X_POS;
	p1->y = PLAYER_INITIAL_Y_POS;
	p1->score = 0;
	p1->life = (bitmap*) bitmap_load("life.bmp");
	return p1;
}

int player_draw(player *p1){
	bitmap_draw(p1->player_ship, p1->x, p1->y, ALIGN_LEFT);

	//Draws score
	font_draw_string(space_invaders_font, 0, 724, "Score: ", ALIGN_LEFT);
	font_draw_int(space_invaders_font, strlen("Score: ")*space_invaders_font->letter_width, 724, p1->score, ALIGN_LEFT);

	//Draws lives
	unsigned short i;
	unsigned short x = get_h_res() - 3*p1->life->bmp_info_header.width - 1;
	for(i = 0; i < p1->num_lives; i++){
		bitmap_draw(p1->life, x+i*p1->life->bmp_info_header.width, get_v_res()-p1->life->bmp_info_header.height - 1, ALIGN_LEFT);
	}
}

int player_fire(player *p1) {
	return projectile_init(p1, (unsigned short) (p1->x+SHIP_WIDTH/2), p1->y-PLAYER_PROJECTILE_HEIGHT, PLAYER_PROJECTILE_WIDTH, PLAYER_PROJECTILE_HEIGHT, -5);
}

int player_hit(player *p1) {	//TODO
	if (p1->num_lives > 1) {
		p1->num_lives--;
		p1->x = PLAYER_INITIAL_X_POS;
		p1->y = PLAYER_INITIAL_Y_POS;
		return 0;
	} else
		return 1;
}

int player_move(player *p1, char direction){
	if(p1->x + direction*SHIP_X_DELTA < 0)
		p1->x = 0;

	if(p1->x + direction*SHIP_X_DELTA + SHIP_WIDTH >= get_h_res())
		p1->x = get_h_res() - SHIP_WIDTH - 1;

	p1->x += direction*SHIP_X_DELTA;
	return 0;
}

int player_set_x_pos(player *p1, unsigned short x){
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

int player_collision_handler(player* p1, struct _projectile* proj){
	if((proj->x > p1->x && proj->x < p1->x + SHIP_WIDTH) && (proj->y > p1->y && proj->y < p1->y + SHIP_HEIGHT)
			|| (proj->x + proj->width > p1->x && proj->x + proj->width < p1->x + SHIP_WIDTH) && (proj->y + proj->height > p1->y && proj->y + proj->height < p1->y + SHIP_HEIGHT)){
		player_hit(p1);
		return 1;
	}
	return 0;
}

void player_destruct(player *p1){
	bitmap_delete(p1->player_ship);
	bitmap_delete(p1->life);
	free(p1);
}
