#ifndef ALIENS_H
#define ALIENS_H

#include <stdio.h>

#include "video_gr.h"
#include "state.h"
#include "proj.h"
#include "player.h"
#include "animation.h"

#define ALIENS_PER_ROW 11
#define ALIEN_ROWS 5
#define INITIAL_X_POS 50
#define INITIAL_Y_POS 20
#define ALIEN_WIDTH 48
#define ALIEN_HEIGHT 32
#define ALIEN_SPACEMENT 10
#define VELOCITY_INCREASE 1
#define ALIEN_X_DELTA ALIEN_WIDTH + ALIEN_SPACEMENT
#define ALIEN_Y_DELTA ALIEN_HEIGHT + ALIEN_SPACEMENT
#define ALIEN_MOVES_PER_COLUMN 8
#define ALIEN_MOVES_PER_ROW 5

#define PLACEHOLDER_LEFT_BORDER 100
#define PLACEHOLDER_RIGHT_BORDER 900  //TODO eliminar
#define PLACEHOLDER_SHIELD_LINE 568

enum alien_type { SMALL, MEDIUM, LARGE, UFO};

typedef struct _alien{
	enum alien_type type;
	int x, y;
	int width, height;
	char *mem_pos;
	struct _alien *next;
	struct _alien *prev;
} alien;

typedef struct {
	alien *head;
	alien *last;
	alien *rightmost;
	alien *leftmost;
	//alien *player_controlled; TODO if we implement vs multiplayer
	int velocity;
	unsigned char alien_num;
	animation *small_alien, *medium_alien, *large_alien, *ufo;
} alien_list;

alien_list* invaders;

/**
 * @brief Initializes the alien linked list.
 */
void alien_list_init();

/**
 * @brief adds alien to the list
 */
void alien_add(alien *a1);

/**
 * @brief removes alien from list
 * @ret 0 if alien is removed, 1 if alien removed is the last adversary, -1 if alien cant be found
 */
int alien_remove(alien *a1);

/**
 * @brief Initializes an alien struct
 *
 * @param xpos initial x position of the alien
 * @param ypos initial y position of the alien
 * @param type type of alien
 */
alien* alien_init(int xpos, int ypos, enum alien_type type);

/**
 * @brief draws the alien
 */
int alien_draw(alien* a1);

/**
 * @brief sets next x and y position of the alien
 */
void alien_move(alien* a1, char x, char y);

/**
 * @brief Moves all the aliens
 *
 *
*/
int aliens_move();

/**
 * @brief Checks if the projectile in x,y collides with an alien
 *
 * @param x Projectile's x position
 * @param y Projectile's y position
 *
 * @return Returns zero if the projectile has not hit an alien, returning non-zero otherwise.
 */
int aliens_collision_handler(unsigned short x, unsigned short y);

/**
 * @brief draws all the aliens
 */
void aliens_draw();

/**
 * @brief searches new leftmost or rightmost alien and updates pointer on list
 * @param side 1 for rightmost, 2 for leftmost
 *
 * @return Returns 0 if a new extreme has been successfully found, returning non-zero otherwise.
 */
int search_new_extreme(unsigned char side);

/**
 * @brief Frees memory when no longer in use
 */
void aliens_destruct();

#endif
