#ifndef ALIENS_H
#define ALIENS_H

#include <stdio.h>

#define ALIENS_PER_ROW 11
#define ALIEN_ROWS 5
#define INITIAL_X_POS 50
#define INITIAL_Y_POS 20
#define ALIEN_WIDTH 45
#define ALIEN_HEIGTH 30
#define ALIEN_SPACEMENT 10
#define ALIEN_X_DELTA 5
#define ALIEN_Y_DELTA 5
#define ALIEN_MOVES_PER_COLUMN 10
#define ALIEN_MOVES_PER_ROW 5

enum alien_type { SMALL, MEDIUM, LARGE, UFO};

typedef struct _alien{
	enum alien_type type;
	unsigned char id;
	int x, y;
	int width, height;
	int velocity;
	char *mem_pos;
	struct _alien *next;
} alien;

typedef struct {
	alien *head;
	unsigned char alien_num;
} alien_list;

alien_list* invaders;

/**
 * @brief Initializes the alien linked list.
 */
void alien_list_init();

/**
 * @brief adds alien to the list
 */
void add_alien(alien *a1);

/**
 * @brief removes alien from list
 */
void remove_alien(alien *a1);

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
int draw_alien(alien* a1);

/**
 * @brief sets next x and y position of the alien
 */
int move_alien(alien* a1, char x, char y);

/**
 * @brief Moves all the aliens
 */
int aliens_move();

/**
 * @brief Checks if the projectile in x,y collides with an alien
 */
int aliens_collision_handler(unsigned short x, unsigned short y);

/**
 * @brief handles the collision of a projectile with the alien
 */
int alien_hit(alien* a1);

#endif
