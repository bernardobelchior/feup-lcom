#include "aliens.h"

void alien_list_init(){

	if((invaders=(alien_list*)malloc(sizeof(alien_list)))== NULL)
		return;

	invaders->alien_num = ALIEN_ROWS * ALIENS_PER_ROW;
	invaders->head = NULL;

	unsigned char row_pos;
	unsigned char line = 1;
	unsigned char counter;
	int x = INITIAL_XPOS;
	int y = INITIAL_YPOS;
	enum alien_type type;

	for(counter = 0; counter <= invaders->alien_num; counter++){

		if(counter % ALIENS_PER_ROW == 	0 ){
			y += ALIEN_HEIGTH+ALIEN_SPACEMENT;
			x = INITIAL_XPOS;
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

void remove_alien(alien *a1);


alien *alien_init(int xpos, int ypos, enum alien_type type){
	alien *et;

	if((et= (alien *)malloc(sizeof(alien))) == NULL )
		return;

	et->xpos = xpos;
	et->ypos=ypos;
	et->type = type;

	et->width = ALIEN_WIDTH;
	et->height = ALIEN_HEIGTH;
	et->next = NULL;
	et->id = invaders->alien_num;
	et->velocity=150;

	return et;
}

int draw_alien(alien *a1){
	vg_draw_frame(a1->xpos,a1->ypos,a1->width,a1->height,9);
}
