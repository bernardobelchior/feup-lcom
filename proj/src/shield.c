#include "shield.h"

int shield_list_init(char mode) {
	shield_left = bitmap_load("left_shield.bmp");
	shield_middle = bitmap_load("middle_shield.bmp");
	shield_right = bitmap_load("right_shield.bmp");

	if(!mode){
		inv_shield_left = bitmap_load("inv_left_shield.bmp");
		inv_shield_middle = bitmap_load("inv_middle_shield.bmp");
		inv_shield_right = bitmap_load("inv_right_shield.bmp");
	}
	else {
		inv_shield_left = NULL;
		inv_shield_middle = NULL;
		inv_shield_right = NULL;
	}

	if ((shields = (shield_list *) malloc(sizeof(shield_list))) == NULL)
		return 1;

	shields->head = NULL;

	unsigned char i = 0;
	unsigned short x = SHIELD_INITIALX;
	unsigned short y;

	if(!mode)
		y = VERSUS_MP_YPOS;
	else y = PLACEHOLDER_SHIELD_LINE;

	for (i = 0; i < NUM_SHIELDS; i++) {

		if (add_shield(shield_init(x, y)) != 0)
			return 1;

		x += SHIELD_WIDTH + SHIELD_SPACEMENT;
	}

	return 0;
}

shield *shield_init(unsigned short x, unsigned short y) {
	shield *s1 = NULL;

	if ((s1 = (shield *) malloc(sizeof(shield))) == NULL)
		return NULL;

	s1->x = x;
	s1->y = y;
	s1->next = NULL;
	s1->prev = NULL;
	s1->list = NULL;

	add_sprite(s1, s1->x + LEFT_SPRITE_DELTA_X, s1->y, SHIELD_SIDE_WIDTH, SHIELD_SIDE_HEIGHT, shield_left);	//Left sprite
	add_sprite(s1, s1->x + MIDDLE_SPRITE_DELTA_X, s1->y, SHIELD_MIDDLE_WIDTH, SHIELD_MIDDLE_HEIGHT, shield_middle);	//Middle sprite
	add_sprite(s1, s1->x + RIGHT_SPRITE_DELTA_X, s1->y, SHIELD_SIDE_WIDTH, SHIELD_SIDE_HEIGHT, shield_right);	//Right sprite

	return s1;
}

int add_sprite(shield *s1, unsigned short x, unsigned short y, unsigned short width, unsigned short height, bitmap* bmp) {

	if (s1 == NULL)
		return 1;

	shield_sprite *sh_sprt;

	if ((sh_sprt = (shield_sprite *) malloc(sizeof(shield_sprite))) == NULL)
		return 1;

	sh_sprt->x = x;
	sh_sprt->y = y;
	sh_sprt->width = width;
	sh_sprt->height = height;
	sh_sprt->durability = SPRITE_DURABILITY;
	sh_sprt->bmp = bmp;
	sh_sprt->next = NULL;
	sh_sprt->prev = NULL;

	if (s1->list == NULL) {
		s1->list = sh_sprt;
		return 0;
	}

	shield_sprite *iterator = s1->list;

	while (iterator->next != NULL) {
		iterator = iterator->next;
	}

	iterator->next = sh_sprt;
	sh_sprt->prev = iterator;

	return 0;
}

int add_shield(shield *s1) {

	if (s1 == NULL)
		return 1;

	if (shields->head == NULL) {
		shields->head = s1;
		return 0;
	}

	shield *iterator = shields->head;

	while (iterator->next != NULL)
		iterator = iterator->next;

	iterator->next = s1;
	s1->prev = iterator;

	return 0;
}

int delete_shield(shield *s1) {

	if (s1 == NULL)
		return 1;

	shield* iterator = shields->head;

	if (s1 == shields->head) {
		if (s1->next == NULL) {
			shields->head = NULL;
			free(s1);
			return 0;
		}

		shields->head = s1->next;
		s1->next->prev = NULL;

		free(s1);
		return 0;
	}

	do {
		if (iterator == s1) {
			iterator->prev->next = s1->next;

			if (s1->next != NULL)
				s1->next->prev = iterator;

			free(s1);
			return 0;
		}

		iterator = iterator->next;
	} while (iterator != NULL);

	return 1;
}

int delete_sprite(shield *s1, shield_sprite *shsp) {

	if (s1 == NULL || shsp == NULL)
		return 1;

	if (shsp == s1->list) {
		if (shsp->next == NULL) {
			if (delete_shield(s1))
				return 1;
			return 0;
		}

		s1->list = shsp->next;
		shsp->next->prev = NULL;
		free(shsp);
		return 0;
	}

	shield_sprite *iterator = s1->list;

	do {
		if (iterator == shsp) {
			iterator->prev->next = shsp->next;

			if (shsp->next != NULL)
				shsp->next->prev = shsp->prev;

			free(shsp);
			return 0;
		}

		iterator = iterator->next;
	} while (iterator != NULL);

	return 1;
}

int shield_draw(shield *s1) {

	if (s1->list == NULL)
		return 1;

	shield_sprite* iterator = s1->list;

	do {
		bitmap_draw(iterator->bmp, iterator->x, iterator->y, ALIGN_LEFT);
		iterator = iterator->next;
	} while (iterator != NULL);

#ifdef DEBUG
	if(s1 == shields->head)
		vg_draw_frame(s1->x,s1->y, 5 , 5, 3);
#endif

}

void shields_draw() {

	if (shields->head == NULL) {
		return;
	}

	shield* iterator = shields->head;

	do {
		shield_draw(iterator);
		iterator = iterator->next;
	} while (iterator != NULL);
}

int shield_collision_handler(projectile* proj) {

	if (shields->head == NULL)
		return 0;

	if (proj->y < shields->head->y || proj->y > shields->head->y + SHIELD_HEIGHT)
		return 0;

	shield* iterator = shields->head;

	do {
		if ((proj->y <= iterator->y + SHIELD_HEIGHT && proj->y >= iterator->y
				&& proj->x <= iterator->x + SHIELD_WIDTH && proj->x >= iterator->x)
				|| (proj->y + proj->height <= iterator->y + SHIELD_HEIGHT && proj->y + proj->height >= iterator->y
						&& proj->x + proj->width <= iterator->x + SHIELD_WIDTH && proj->x + proj->width >= iterator->x))
			return sprite_hit(iterator, proj);

		iterator = iterator->next;
	} while (iterator != NULL);

	return 0;
}

int sprite_hit(shield *s1, projectile* proj) {

	if (s1 == NULL)
		return 0;

	shield_sprite *iterator = s1->list;

	do {
		if ((proj->y <= iterator->y + iterator->height && proj->y >= iterator->y
				&& proj->x <= iterator->x + iterator->width && proj->x >= iterator->x) ||
				(proj->y + proj->height <= iterator->y + iterator->height && proj->y + proj->height >= iterator->y
						&& proj->x + proj->width <= iterator->x + iterator->width && proj->x + proj->width >= iterator->x)){
			iterator->durability--;
			if (!iterator->durability)
				delete_sprite(s1, iterator);
			return 1;
		}

		iterator = iterator->next;
	} while (iterator != NULL);

	return 0;
}

void shields_destruct() {

	if (shields->head == NULL)
		return;

	while (shields->head != NULL)
		delete_shield(shields->head);
}
