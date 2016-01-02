#ifndef ALIENS_H
#define ALIENS_H

#include "animation.h"
#include "projectile.h"

#define ALIENS_PER_ROW 11
#define ALIEN_ROWS 5
#define INITIAL_X_POS 50
#define INITIAL_Y_POS 20
#define ALIEN_WIDTH 48
#define ALIEN_HEIGHT 32
#define ALIEN_SPACEMENT 10
#define MOVEMENT_INCREASE 1
#define INITIAL_MOV_FREQ 90
#define ALIEN_X_DELTA 15
#define ALIEN_Y_DELTA ALIEN_HEIGHT + ALIEN_SPACEMENT
#define ALIEN_MOVES_PER_COLUMN 8
#define ALIEN_MOVES_PER_ROW 5
#define ALIEN_PROJECTILE_WIDTH 5
#define ALIEN_PROJECTILE_HEIGHT 10
#define LARGE_ALIEN_SCORE 1
#define MEDIUM_ALIEN_SCORE 2
#define SMALL_ALIEN_SCORE 3
#define UFO_ALIEN_SCORE 5
#define ALIEN_PROJECTILE_VELOCITY 3

#define PLACEHOLDER_LEFT_BORDER 100
#define PLACEHOLDER_RIGHT_BORDER 900  //TODO eliminar
#define PLACEHOLDER_SHIELD_LINE 568

enum alien_type { SMALL, MEDIUM, LARGE, UFO};
enum alien_state { ALIEN_ALIVE, ALIEN_DESTROYED };

typedef struct _alien{
	unsigned short ticks;
	enum alien_type type;
	enum alien_state state;
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
	unsigned char alien_num;
	animation *small_alien, *medium_alien, *large_alien, *ufo, *destroy;
	int movement_frequency;
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
 * @param width Projectile's width
 * @param height Projectile's height
 *
 * @return Returns zero if the projectile has not hit an alien, returning non-zero otherwise.
 */
int aliens_collision_handler(projectile* proj);

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
 * @brief fires a projectile
 */
int alien_fire(alien *a1);

/**
 * @brief Handles ticks in aliens
 */
void aliens_tick();

/**
 * @brief checks if the alien is on the row closest to the player(s)
 */
int is_on_last_row(alien *a1);

/**
 * @brief Frees memory when no longer in use
 */
void aliens_destruct();

#endif
