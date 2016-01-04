#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "shield.h"
#include "state.h"
#include "rtc.h"
#include "game_over_menu.h"

/** @defgroup singleplayer singleplayer
 * @{
 * singleplayer
 */

typedef struct {
	shield* (*shields);
	player* play;
	unsigned int score;
	unsigned char reset_ticks;
} game_t;

game_t singleplayer_game;

extern game_over_info new_score;

/**
 * @brief Initializes singleplayer game information
 */
void singleplayer_init();

/**
 * @brief Event called when a tick occurs and the game state is singleplayer.
 */
void singleplayer_tick();

/**
 * \brief calls the player_fire function
 */
int singleplayer_fire();
/**
 * @brief Moves the player in the x axis
 *
 * @param direction -1 to move to the left, 1 to the right.
 *
 * @return Returns 0 if the new position is valid, non-zero otherwise.
 */
int singleplayer_move(char direction);

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

/*/
 * @brief randomly chooses alien to fire
 */
alien *singleplayer_alien_to_fire();

/**
 * @brief Deletes the game and goes to main menu
 */
void singleplayer_game_over();

/**
 * @brief Deletes singleplayer game information
 */
void singleplayer_destruct();

#endif
