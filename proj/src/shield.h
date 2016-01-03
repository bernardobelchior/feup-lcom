#ifndef SHIELD_H
#define SHIELD_H

#include <stdio.h>
#include "aliens.h"

#define NUM_SHIELDS 4

#define SHIELD_SPACEMENT 60
#define SHIELD_SIDE_HEIGHT 63
#define SHIELD_MIDDLE_HEIGHT 47
#define SHIELD_SIDE_WIDTH 45
#define SHIELD_MIDDLE_WIDTH 35
#define SHIELD_WIDTH 2*SHIELD_SIDE_WIDTH + SHIELD_MIDDLE_WIDTH
#define SHIELD_HEIGHT SHIELD_SIDE_HEIGHT

#define SHIELD_INITIALX PLACEHOLDER_LEFT_BORDER + SHIELD_SPACEMENT
#define VERSUS_MP_YPOS 384

#define SPRITE_DURABILITY 3

#define LEFT_SPRITE_DELTA_X 0
#define MIDDLE_SPRITE_DELTA_X 45
#define RIGHT_SPRITE_DELTA_X 80

typedef struct _sh_sprite{
	unsigned short x, y;
	unsigned short width, height;
	char durability;
	bitmap *bmp;
	struct _sh_sprite *next;
	struct _sh_sprite *prev;
} shield_sprite;

typedef struct _shield{
	unsigned short x, y;
	shield_sprite *list;
	struct _shield *next;
	struct _shield *prev;
} shield;

typedef struct {
	shield *head;
} shield_list;

shield_list *shields;
bitmap *shield_left, *shield_middle, *shield_right;
bitmap *inv_shield_left, *inv_shield_middle, *inv_shield_right;

/**
 * \brief initializes a linked list for the shields
 * @param mode 0 for versus multiplayer, != 0 for other modes
 */
int shield_list_init(char mode);

/**
 * \brief intializes the shield struct
 *
 * @param x x position of the leftmost border of the shield
 * @param y y position of the top border of the shield
 */
shield *shield_init(unsigned short x, unsigned short y);

/**
 * \brief initializes and adds a sprite to the shield list
 *
 * @param s1 shield to put the sprite
 * @param x leftmost position of the sprite
 * @param y top position of the sprite
 * @param width sprite width
 * @param height sprite height
 * @param bmp sprite image
 */
int add_sprite(shield *s1, unsigned short x, unsigned short y, unsigned short width, unsigned short height, bitmap* bmp);

/**
 * \brief adds the shield to the linked shield list
 */
int add_shield(shield *s1);

/**
 *\brief deletes a shield sprite
 *
 *@param s1 shield where the sprite is
 *@param shsp sprite to delete
 */
int delete_sprite(shield *s1, shield_sprite *shsp);

/**
 * \brief deletes the shield struct
 *
 * @param s1 shield to delete
 */
int delete_shield(shield *s1);

/**
 * \brief places the shield on the screen
 *
 * @param s1 shield to draw
 */
int shield_draw(shield *s1);

/**
 * \brief draws all the shields on the list
 */
void shields_draw();

/**
 * \brief checks if a projectile collided with one of the shields
 *
 * @param proj projectile to check
 */
int shield_collision_handler(projectile* proj);

/**
 * \brief handles the collision of a projectile and a shield, check what sprite was hit
 *
 * @param s1 shield that was hit
 * @param proj projectile
 */
int sprite_hit(shield *s1, projectile* proj);

/**
 * \brief deletes the list and any remaining shields
 */
void shields_destruct() ;

#endif
