#ifndef __PLAYER_SHIP_H
#define __PLAYER_SHIP_H

#include "keyboard.h"
#include "timer.h"
#include "video_gr.h"
#include "projectile.h"
#include <stdlib.h>
#include <stdio.h>

#define NUM_LIVES 3
#define PLAYER_INITIAL_X_POS 512
#define PLAYER_INITIAL_Y_POS 700
#define SHIP_WIDTH 50
#define SHIP_HEIGHT 30

typedef struct{
	int num_lives;
	int x, y;
	int velocity;
	unsigned char *mem_pos;
} player;

player* player_init(); //allocates the struct and set num_lives
int player_set_x_pos(player *p1, unsigned short x); //Sets player x position
int player_move(player *p1, short x); //Keyboard interrupt handler for left and right arrow keys
int player_draw(player *p1); //Places the cannon on the screen
projectile *player_fire(player *p1); //Function called when there is a event for the player to fire
void player_hit(player *p1); //Decreases lives and animation for the player destruction when he dies
int player_check_collision(player* p1, unsigned short x, unsigned short y); //Check if the object collides with player
int player_game_over(player *p1); //Calls player destruct and goes to game over screen
void player_destruct(player *p1); //Frees p1

#endif /*__PLAYER_SHIP_H*/
