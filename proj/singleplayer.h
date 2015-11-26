#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "aliens.h"
#include "shield.h"
#include "player_ship.h"

typedef struct {
	alien* (*aliens);
	shield* (*shields);
	player* play;
	projectile* (*projectiles);
	unsigned char num_projectiles;
	unsigned int score;
} game_t;

game_t singleplayer_game;

#define ALIENS_PER_ROW 10
#define ALIEN_ROWS 4
#define NUMBER_OF_SHIELDS 4

/**
 * @brief Initializes singleplayer game information
 */
void singleplayer_init();

/**
 * @brief Event called when a tick occurs and the game state is singleplayer.
 */
void singleplayer_tick();

/**
 * @brief Moves the player in the x axis
 *
 * @param Difference on x position
 *
 * @return Returns 0 if the new position is valid, non-zero otherwise.
 */
int singleplayer_move(short x);

/**
 * @brief Sets the player position to x
 *
 * @param Position in the x axis
 *
 * @return Returns 0 if the position is valid, non-zero otherwise.
 */
int singleplayer_set_x_pos(unsigned short x);

/**
 * @brief Checks whether each one of the projectiles collide with any object or has reached the end of screen. If it did, deletes it.
 */
void singleplayer_check_projectiles_state();

/**
 * @brief Check if the projectile collides with any object and handles its consequences.
 *
 * @param proj Projectile to check collisions
 *
 * @return Returns 0 if the projectile does not collide with anything, returning non-zero otherwise.
 */
int singleplayer_projectile_collision(projectile* proj);

/**
 * @brief Deletes projectile at proj_index and rearranges the array.
 *
 * @return Returns 0 if the deletion was successful, returning non-zero otherwise.
 */
int singleplayer_delete_projectile(unsigned int proj_index);

/**
 * @brief Deletes singleplayer game information
 */
void singleplayer_destruct();

#endif
