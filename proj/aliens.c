#include "aliens.h"

void alien_list_init(){

	if((invaders=(alien_list*)malloc(sizeof(alien_list)))== NULL)
		return;

	invaders->alien_num = ALIEN_ROWS * ALIENS_PER_ROW;
	invaders->head = NULL;

	unsigned char row_pos;
	unsigned char line = 1;
	unsigned char counter;
	int x = INITIAL_X_POS;
	int y = INITIAL_Y_POS;
	enum alien_type type;

	for(counter = 0; counter <= invaders->alien_num; counter++){

		if(counter % ALIENS_PER_ROW == 	0 ){
			y += ALIEN_HEIGTH+ALIEN_SPACEMENT;
			x = INITIAL_X_POS;
			line++;
		}

		else
			x += ALIEN_WIDTH + ALIEN_SPACEMENT;

		if(line == 1)
			type=1;

		else if( line == 2 || line == 3)
			type = 2;

		else if(line == 4 || line == 5)
			type = 3;


		add_alien((alien_init(x,y,type)));
	}
}


void add_alien(alien *a1){

	if(invaders->head == NULL){
		invaders->head = a1;
		return;
	}

	alien* iterator = invaders->head;

	while(iterator->next != NULL)
		iterator=iterator->next;

	iterator->next = a1;

}

void remove_alien(alien *a1){
	alien* iterator = invaders->head;

	while(iterator->next != NULL){
		if(iterator->next == a1){
			iterator->next = iterator->next->next;
			free(a1);
			break;
		}
		iterator = iterator->next;
	}
}

int aliens_move(){
	static unsigned char moves = 0;
	static char direction = -1;

	if(moves == ALIEN_MOVES_PER_COLUMN*ALIEN_MOVES_PER_ROW)
		return 1;

	alien* iterator = invaders->head;

	if(moves % ALIEN_MOVES_PER_COLUMN == 0){ //if the aliens have moved enough for this row
		while(iterator->next != NULL){
			move_alien(iterator, 0, ALIEN_Y_DELTA);
			iterator=iterator->next;
		}
		direction = (-1)*direction;
	} else
		while(iterator->next != NULL){
			move_alien(iterator, direction*ALIEN_X_DELTA, 0);
			iterator=iterator->next;
		}

	moves++;
	return 0;
}

int move_alien(alien* a1, char x, char y){
	a1->x += x;
	a1->y += y;
}

alien *alien_init(int x, int y, enum alien_type type){
	alien *et;

	if((et= (alien *)malloc(sizeof(alien))) == NULL )
		return;

	et->x = x;
	et->y=y;
	et->type = type;

	et->width = ALIEN_WIDTH;
	et->height = ALIEN_HEIGTH;
	et->next = NULL;
	et->id = invaders->alien_num;
	et->velocity=150;

	return et;
}

int aliens_collision_handler(unsigned short x, unsigned short y){
	unsigned short rightmost_collision_point, lowest_collision_point;
	rightmost_collision_point = invaders->head->x + ALIEN_WIDTH*ALIENS_PER_ROW + (ALIENS_PER_ROW-1)*ALIEN_SPACEMENT;
	lowest_collision_point = invaders->head->y + ALIEN_HEIGTH*ALIEN_ROWS + (ALIEN_ROWS-1)*ALIEN_SPACEMENT;

	if(x > invaders->head->x && x < rightmost_collision_point && y > invaders->head->y && y < lowest_collision_point){
		alien* iterator = invaders->head;
		while(iterator->next != NULL){
			if(x > iterator->x && x < iterator->x + ALIEN_WIDTH && y > iterator->y && y < iterator->y + ALIEN_HEIGTH){
				remove_alien(iterator);
				return 1;
			}
			iterator=iterator->next;
		}
	}

	return 0;
}

int draw_alien(alien *a1){
	vg_draw_frame(a1->x,a1->y,a1->width,a1->height,9);
}
