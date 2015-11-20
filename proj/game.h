#ifndef GAME_H
#define GAME_H

#include "aliens.h"
#include "shield.h"

#define ALIENS_PER_ROW 10
#define ALIEN_ROWS 4
#define NUMBER_OF_SHIELDS 4

typedef struct {
	Alien* aliens;
	Shield* shields;
	player play;
} game;

game singleplayer;

/**
 * @brief Initializes game information
 */
void game_init();

/**
 * @brief Deletes the game information
 */
void game_destruct();

#endif
