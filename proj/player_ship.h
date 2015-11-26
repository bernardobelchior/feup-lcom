#ifndef __PLAYER_SHIP_H
#define __PLAYER_SHIP_H

#include "keyboard.h"
#include "timer.h"
#include "video_gr.h"
#include <stdlib.h>
#include <stdio.h>

#define NUM_LIVES 3
#define INITIAL_CANNON_POS 512
#define INITIAL_SHIP_POS 700
#define SHIP_WIDTH 50
#define SHIP_HEIGHT 30

typedef struct{
	int num_lives;
	int ypos, cannonxpos;
	int velocity;
	unsigned char *mem_pos;
} player;

player* player_init(); //allocates the struct and set num_lives
int move_player(player *p1, short x); //Keyboard interrupt handler for left and right arrow keys
int draw_player(player *p1); //Places the cannon on the screen
int player_fire(player *p1); //Keyboard handler for Spacebar (in singleplayer)
void player_hit(player *p1); //Animation for the player destruction
int player_game_over(player *p1); //Calls player destruct and goes to game over screen
void player_destruct(player *p1); //Frees p1

#endif /*__PLAYER_SHIP_H*/
