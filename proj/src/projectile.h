#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdio.h>

#define END_AT_TOP 50
#define END_AT_BOTTOM 700


//typedef enum {CANNON, ALIEN} shooter;

typedef struct _projectile{
	unsigned short x ,y;
	int velocity;
	struct _projectile *next;
	struct _projectile *prev;
} projectile;

typedef struct{
	projectile *head;
} projectile_list;

projectile_list *projectiles;

/**
 * @brief Initializes the projectile linked list.
 */
void projectile_list_init();

/**
 * @brief initializes the projectile struct and adds it to the list
 * @param x x position of the projectile
 * @param y y position of the projectile
 * @param velocity velocity of the projectile
 */
int projectile_init(unsigned short x, unsigned short y, int velocity);

/**
 * @brief draws the projectile
 * @param proj projectile to draw
 */
int projectile_draw(projectile *proj);
int projectile_delete(projectile *proj);
int projectile_move(projectile *proj);
int collision(projectile* proj, unsigned char color, unsigned short x, unsigned short y); //checks what kind of target was hit and throws the appropriate destruction event
int alien_collision(unsigned short x, unsigned short y);
int player_collision();
int shield_collision(unsigned short x, unsigned short y);
int projectile_reached_end(projectile *proj);

#endif
