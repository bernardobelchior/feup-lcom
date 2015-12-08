#ifndef SHIELD_H
#define SHIELD_H

#include <stdio.h>
#include "aliens.h"

#define NUM_SHIELDS 4

#define SHIELD_SPACEMENT 100
#define SHIELD_WIDTH 100
#define SHIELD_HEIGHT 50

#define SHIELD_INITIALX PLACEHOLDER_LEFT_BORDER + SHIELD_SPACEMENT

#define SPRITES_PER_SHIELD 10

#define SPRITE_DURABILITY 3
#define SPRITE_HEIGHT 25
#define SPRITE_WIDTH 10


#define sprite


typedef struct _sh_sprite{
	unsigned int xpos, ypos;
	char durability;
	struct _sh_sprite *next;
	struct _sh_sprite *prev;
} shield_sprite;

typedef struct _shield{
	unsigned int xpos, ypos;
	shield_sprite *list;
	struct _shield *next;
	struct _shield *prev;
} shield;

typedef struct {
	shield *head;
} shield_list;

shield_list *shields;

int shield_list_init();
shield *shield_init(unsigned int x, unsigned int y);
int add_sprite(shield *s1,unsigned int x, unsigned int y);
int add_shield(shield *s1);
int delete_sprite(shield *s1, shield_sprite *shsp);
int delete_shield(shield *s1);
int shield_draw(shield *s1);
void shields_draw();
int shield_collision_handler(unsigned short x, unsigned short y);
int sprite_hit(shield *s1, unsigned short x, unsigned short y);
void shields_destruct() ;

#endif
