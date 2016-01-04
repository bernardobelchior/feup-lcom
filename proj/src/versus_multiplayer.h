#ifndef VERSUS_MP_H
#define VERSUS_MP_H

#include "state.h"
#include "singleplayer.h"

/** @defgroup versus_multiplayer versus_multiplayer
 * @{
 * versus multiplayer
 */

#define DEFAULT_TIME_LIMIT 		90 //in seconds
#define GAME_OVER_SCREEN_TIME 	5

typedef struct{
	player* p1;
	player* p2;
	unsigned char reset_ticks;
} versus_mp_game;

versus_mp_game mp_game;

/**
 * \brief Initalizes versus mode multiplayer game information
 */
void versus_mp_game_init();

/**
 * \brief Event called when a tick occurs and the state is versus multiplayer
 */
void versus_mp_game_tick();

/**
 * \brief Moves a player in the x axis
 *
 * @param player Player to move (1 or 2)
 * @param direction direction in which to move the player, 1 to right, -1 to left
 */
int versus_mp_move(char player, char direction);

/**
 * \brief calls the player_fire funtion for the selected Player
 *
 * @param player player to fire (1 or 2)
 */
int versus_mp_fire(char player);

/**
 * \brief Checks whether each one of the projectiles collide with any object or has reached the end of screen. If it did, deletes it.
 */
void versus_mp_check_projectiles_state();

/**
 * @brief Check if the projectile collides with any object and handles its consequences.
 *
 * @param proj Projectile to check collisions
 *
 * @return Returns 0 if the projectile does not collide with anything, returning non-zero otherwise.
 */
int versus_mp_projectile_collision(projectile *proj);


/**
 * \brief Deletes the versus_mp_game struct
 */
void versus_mp_game_destruct();



#endif
