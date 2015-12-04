#include "aliens.h"
#include "video_gr.h"
#include "state.h"
#include "proj.h"

static char direction;

void alien_list_init() {

	//moves = 0;
	direction = 1;

	if ((invaders = (alien_list*) malloc(sizeof(alien_list))) == NULL)
		return;

	invaders->alien_num = ALIEN_ROWS * ALIENS_PER_ROW;
	invaders->head = NULL;
	invaders->last = NULL;
	invaders->velocity = ALIEN_X_DELTA;

	unsigned char row_pos;
	unsigned char line = 1;
	unsigned char counter;
	int x = INITIAL_X_POS;
	int y = INITIAL_Y_POS;
	enum alien_type type;

	for (counter = 0; counter < invaders->alien_num; counter++) {

		if (counter % ALIENS_PER_ROW == 0) {
			y += ALIEN_HEIGHT + ALIEN_SPACEMENT;
			x = INITIAL_X_POS;
			line++;
		}

		else
			x += ALIEN_WIDTH + ALIEN_SPACEMENT;

		if (line == 1)
			type = 1;

		else if (line == 2 || line == 3)
			type = 2;

		else if (line == 4 || line == 5)
			type = 3;

		alien_add((alien_init(x, y, type)));
	}

	search_new_extreme(1);
	search_new_extreme(2);
}

void alien_add(alien *a1) {

	if (invaders->head == NULL) {
		invaders->head = a1;
		invaders->last = a1;
		return;
	}

	invaders->last->next = a1;
	a1->prev = invaders->last;
	invaders->last = a1;
}

void alien_remove(alien *a1) {
	unsigned char flag = 0;

	if (invaders->rightmost == a1)
		flag = 1;

	else if (invaders->leftmost == a1)
		flag = 2;

	if (invaders->head == a1) {

		if (invaders->last == a1) {
			invaders->head = NULL;
			change_state(main_menu); //TODO game over screen
			return;
		}

		invaders->head = invaders->head->next;
		free(a1);
		invaders->head->prev = NULL;
		invaders->velocity += VELOCITY_INCREASE;
		if (!flag)
			return;
		else {
			search_new_extreme(flag);
			return;
		}
	}

	if (invaders->last == a1) {

		invaders->last = a1->prev;
		a1->prev->next = NULL;
		free(a1);

		if (!flag)
			return;
		else {
			search_new_extreme(flag);
			return;
		}
	}

	alien* iterator = invaders->head;
	do {
		if (iterator->next == a1) {
			iterator->next = iterator->next->next;
			free(a1);
			iterator->next->prev = iterator;
			invaders->velocity += VELOCITY_INCREASE;

			if (!flag)
				return;
			else {
				search_new_extreme(flag);
				return;
			}
		}

		iterator = iterator->next;
	} while (iterator != NULL);
}

int aliens_move() {

	alien* iterator = invaders->head;

	if ((direction == -1
			&& invaders->leftmost->x + direction * invaders->velocity
					< PLACEHOLDER_LEFT_BORDER)
			|| (direction == 1
					&& invaders->rightmost->x + invaders->rightmost->width
							+ invaders->velocity > PLACEHOLDER_RIGHT_BORDER)) {

		if (invaders->last->prev->y + ALIEN_Y_DELTA > PLACEHOLDER_SHIELD_LINE) {
			singleplayer_destruct();
			start_menu_init();
		}

		do {
			alien_move(iterator, 0, ALIEN_Y_DELTA);
			iterator = iterator->next;
		} while (iterator != NULL);

		direction = (-1) * direction;

	} else
		do {
			alien_move(iterator, direction * invaders->velocity, 0);
			iterator = iterator->next;
		} while (iterator != NULL);

	return 0;
}

int alien_draw(alien *a1) {
	vg_draw_frame(a1->x, a1->y, a1->width, a1->height, rgb(0x00FFFFFF));
#ifdef DEBUG
	if (invaders->last == a1)
	vg_draw_frame(a1->x + a1->width / 2, a1->y + a1->height / 2, 5, 5, rgb(0xCC0000));
	if (invaders->head == a1)
	vg_draw_frame(a1->x + a1->width / 2, a1->y + a1->height / 2, 5, 5, rgb(0x00FF00));
	if (invaders->leftmost == a1)
	vg_draw_frame(a1->x + a1->width / 2, a1->y + a1->height / 2, 5, 5, rgb(0xCC0066));
	if (invaders->rightmost == a1)
	vg_draw_frame(a1->x + a1->width / 2, a1->y + a1->height / 2, 5, 5, rgb(0xFFFF00));
#endif
}

int alien_move(alien* a1, char x, char y) {
	a1->x += x;
	a1->y += y;
}

alien *alien_init(int x, int y, enum alien_type type) {
	alien *et;

	if ((et = (alien *) malloc(sizeof(alien))) == NULL)
		return;

	et->x = x;
	et->y = y;
	et->type = type;

	et->width = ALIEN_WIDTH;
	et->height = ALIEN_HEIGHT;
	et->next = NULL;
	et->prev = NULL;

	return et;
}

int aliens_collision_handler(unsigned short x, unsigned short y) {
	unsigned short rightmost_collision_point, lowest_collision_point;

	rightmost_collision_point = invaders->head->x + ALIEN_WIDTH * ALIENS_PER_ROW
			+ (ALIENS_PER_ROW - 1) * ALIEN_SPACEMENT;
	lowest_collision_point = invaders->head->y + ALIEN_HEIGHT * ALIEN_ROWS
			+ (ALIEN_ROWS - 1) * ALIEN_SPACEMENT;

	if (x > invaders->head->x && x < rightmost_collision_point
			&& y > invaders->head->y && y < lowest_collision_point) {
		alien* iterator = invaders->head;

		do {
			if (x > iterator->x && x < iterator->x + ALIEN_WIDTH &&
				y > iterator->y && y < iterator->y + ALIEN_HEIGHT) {
				alien_remove(iterator);
				return 1;
			}
			iterator = iterator->next;
		} while (iterator != NULL);
	}

	return 0;
}

int search_new_extreme(unsigned char side) {

	unsigned short left = get_h_res();
	unsigned short right = 0;

	alien* new_extreme = NULL; //extreme

	alien* iterator = invaders->head;

	if (side == 1) { //searches rightmost
		do {
			if (iterator->x + iterator->width > right) {
				right = iterator->x + iterator->width;
				new_extreme = iterator;
			}

			iterator = iterator->next;
		} while (iterator != NULL);

		invaders->rightmost = new_extreme;

		return 0;
	}

	else if (side == 2) { //searches leftmost
		do {
			if (iterator->x < left) {
				left = iterator->x;
				new_extreme = iterator;
			}

			iterator = iterator->next;
		} while (iterator != NULL);

		invaders->leftmost = new_extreme;

		return 0;
	}

	return 1;

}

void aliens_draw() {

	if (invaders->head == NULL)
		return;

	alien* iterator = invaders->head;

	do {
		alien_draw(iterator);
		iterator = iterator->next;
	} while (iterator != NULL);
}

void aliens_destruct() {
	alien* it = invaders->head;
	alien* end = invaders->last;

	if (invaders->alien_num > 1) {
		while (it != end) {
			it = it->next;
			free(it->prev);
		}
		free(invaders->last);
	}
	else if (invaders->alien_num == 1)
		free(invaders->last);

	free(invaders);
}
