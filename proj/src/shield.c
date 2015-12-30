#include "shield.h"

int shield_list_init(char mode) {

	if ((shields = (shield_list *) malloc(sizeof(shield_list))) == NULL)
		return 1;

	shields->head = NULL;

	unsigned char i = 0;
	unsigned int x = SHIELD_INITIALX;
	unsigned int y;

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

shield *shield_init(unsigned int x, unsigned int y) {

	shield *s1 = NULL;

	if ((s1 = (shield *) malloc(sizeof(shield))) == NULL)
		return NULL;

	s1->xpos = x;
	s1->ypos = y;
	s1->next = NULL;
	s1->prev = NULL;
	s1->list = NULL;

	unsigned char i = 0;
	unsigned int xi = s1->xpos;
	unsigned int yi = s1->ypos;

	for (i = 0; i < SPRITES_PER_SHIELD; i++) {
		if (add_sprite(s1, xi, yi) != 0) {
			return NULL;
		}

		xi += SPRITE_WIDTH;

		if (i == SPRITES_PER_SHIELD / 2 - 1) {
			yi += SPRITE_HEIGHT;
			xi = s1->xpos;
		}
	}

	return s1;
}

int add_sprite(shield *s1, unsigned int x, unsigned int y) {

	if (s1 == NULL)
		return 1;

	shield_sprite *sh_sprt;

	if ((sh_sprt = (shield_sprite *) malloc(sizeof(shield_sprite))) == NULL)
		return 1;

	sh_sprt->xpos = x;
	sh_sprt->ypos = y;
	sh_sprt->durability = SPRITE_DURABILITY;
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
		vg_draw_frame(iterator->xpos, iterator->ypos, SPRITE_WIDTH,
				SPRITE_HEIGHT, rgb(0x00FFFFFF));
		iterator = iterator->next;
	} while (iterator != NULL);

#ifdef DEBUG
	if(s1 == shields->head)
		vg_draw_frame(s1->xpos,s1->ypos, 5 , 5, 3);
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

	if (proj->y < shields->head->ypos || proj->y > shields->head->ypos + SHIELD_HEIGHT)
		return 0;

	shield* iterator = shields->head;

	do {
		if ((proj->y <= iterator->ypos + SHIELD_HEIGHT && proj->y >= iterator->ypos
				&& proj->x <= iterator->xpos + SHIELD_WIDTH && proj->x >= iterator->xpos)
				|| (proj->y + proj->height <= iterator->ypos + SHIELD_HEIGHT && proj->y + proj->height >= iterator->ypos
				&& proj->x + proj->width <= iterator->xpos + SHIELD_WIDTH && proj->x + proj->width >= iterator->xpos))
		return (sprite_hit(iterator, proj->x, proj->y));

		iterator = iterator->next;
	} while (iterator != NULL);

	return 0;
}

int sprite_hit(shield *s1, unsigned short x, unsigned short y) {

	if (s1 == NULL)
		return 0;

	shield_sprite *iterator = s1->list;

	do {
		if (y <= iterator->ypos + SPRITE_HEIGHT && y >= iterator->ypos
				&& x <= iterator->xpos + SPRITE_WIDTH && x >= iterator->xpos) {
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
