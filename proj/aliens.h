#ifndef ALIENS_H
#define ALIENS_H

#include <stdio.h>

#define ALIENS_PER_ROW 11
#define ALIEN_ROWS 5
#define INITIAL_XPOS 250
#define INITIAL_YPOS 100
#define ALIEN_WIDTH 20
#define ALIEN_HEIGTH 10

enum alien_type { SMALL, MEDIUM, LARGE, UFO};

typedef struct _alien{
	enum alien_type type;
	unsigned char id;
	int xpos, ypos;
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

/*
 * @brief sets next x and y position of the alien
 */
int move_alien(alien* a1);

/*
 * @brief handles the collision of a projectile with the alien
 */
int alien_hit(alien* a1);

#endif
