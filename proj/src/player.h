#ifndef __PLAYER_SHIP_H
#define __PLAYER_SHIP_H

#include "keyboard.h"
#include "timer.h"
#include "video_gr.h"
#include "projectile.h"
#include <stdlib.h>
#include <stdio.h>
#include "bitmap.h"

#define NUM_LIVES 3
#define PLAYER_INITIAL_X_POS 512
#define PLAYER_INITIAL_Y_POS 668
#define SHIP_WIDTH 50
#define SHIP_HEIGHT 30
#define SHIP_X_DELTA 20

static char SHIP_RES_NAME[] = "ufo.bmp";

typedef struct{
	int num_lives;
	int x, y;
	int velocity;
	bitmap* player_ship;
} player;

player* player_init(); //allocates the struct and set num_lives
int player_set_x_pos(player *p1, unsigned short x); //Sets player x position
int player_move(player *p1, char direction); //Keyboard interrupt handler for left and right arrow keys
int player_draw(player *p1); //Places the cannon on the screen
int player_fire(player *p1); //Function called when there is a event for the player to fire
void player_hit(player *p1); //Decreases lives and animation for the player destruction when he dies
int player_collision_handler(player* p1, unsigned short x, unsigned short y); //Check if the object collides with player
void player_game_over(player *p1); //Calls player destruct and goes to game over screen
void player_destruct(player *p1); //Frees p1

#endif /*__PLAYER_SHIP_H*/
