#ifndef SHIELD_H
#define SHIELD_H

#include <stdio.h>
#include "aliens.h"

#define NUM_SHIELDS 4

#define SHIELD_SPACEMENT 100
#define SHIELD_WIDTH 100
#define SHIELD_HEIGHT 50

#define SHIELD_INITIALX PLACEHOLDER_LEFT_BORDER + SHIELD_SPACEMENT
#define VERSUS_MP_YPOS 384

#define SPRITES_PER_SHIELD 10

#define SPRITE_DURABILITY 1
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
shield *shield_init(unsigned int x, unsigned int y);

/**
 * \brief initializes and adds a sprite to the shield list
 *
 * @param s1 shield to put the sprite
 * @param x leftmost position of the sprite
 * @param y top position of the sprite
 */
int add_sprite(shield *s1,unsigned int x, unsigned int y);

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
 * @param x position of the projectile
 * @param y position of the projectile
 */
int sprite_hit(shield *s1, unsigned short x, unsigned short y);

/**
 * \brief deletes the list and any remaining shields
 */
void shields_destruct() ;

#endif
