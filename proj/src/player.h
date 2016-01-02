#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H

#include "projectile.h"
#include "bitmap.h"
#include "font.h"
#include "video_gr.h"

#define NUM_LIVES 3
#define SHIP_WIDTH 68
#define SHIP_HEIGHT 30
#define PLAYER_INITIAL_X_POS (unsigned) get_h_res()/2-SHIP_WIDTH/2
#define SP_PLAYER_INITIAL_Y_POS (unsigned) 9*get_v_res()/10
#define MP_PLAYER_1_INITIAL_Y_POS (unsigned) get_v_res()/10
#define SHIP_X_DELTA 20
#define PLAYER_PROJECTILE_WIDTH 5
#define PLAYER_PROJECTILE_HEIGHT 10

struct _projectile;

enum player_state { PLAYER_ALIVE, PLAYER_DESTROYED };

typedef struct _player{
	enum player_state state;
	unsigned short ticks;
	int num_lives;
	int x, y, initial_y;
	int velocity;
	bitmap* player_ship;
	bitmap* life;
	bitmap* destroy;
	unsigned int score;
} player;

static char SHIP_RES_NAME[] = "player_ship.bmp";

extern font* space_invaders_font;

/**
 * @brief Initializes player
 *
 * @param player_num 0 for singleplayer/player 2 in versus mp, 1 for player 1 in versus mp
 * @return Returns player
 */
player* player_init(char player_num);

/**
 * @brief Sets the player x position. Used with mouse.
 *
 * @param p1 Player
 * @param x New position
 *
 * @return Returns 0 if the position was successfully set, returning non-zero otherwise.
 */
int player_set_x_pos(player *p1, unsigned short x);

/**
 * \brief Sets the player y position. Used to place the players in versus mode
 *
 * @param p1 Player
 * @param y New position
 */
int player_set_y_pos(player *p1, unsigned short y);
/**
 * @brief Moves the player in the specified direction
 *
 * @param p1 Player to move
 * @param direction Direction modifier. Negative is left, positive is right.
 *
 * @return Returns 0 if the player has moved successfully.
 */
int player_move(player *p1, char direction);

/**
 * @brief Draws the player, its score and lives
 *
 * @param p1 Player to draw.
 *
 * @return Returns 0 if the players was drawn successfully, returning non-zero otherwise.
 */
int player_draw(player *p1);

/**
 * @brief Makes the player fire a projectile
 *
 * @param p1 Player
 * @param direction direction to fire, 1 == up, -1 == down
 *
 * @return Returns 0 if the projectile was successfully created, returning non-zero otherwise.
 */
int player_fire(player *p1,char direction);

/**
 * @brief Handles the player being hit by a projectile.
 *
 * @param p1 Player

 *
 * @return Returns 1 if the player has no more lives, returning 0 otherwise.
 */
int player_hit(player *p1);

/**
 * @brief Handles the collision between the player and a projectile.
 *
 * @param p1 Player
 * @param proj Projectile
 *
 * @return Returns if the player was hit, returning 0 otherwise.
 */
int player_collision_handler(player* p1, struct _projectile* proj);

/**
 * @brief Mirrors player ship image. Useful on multiplayer.
 *
 * @param p1 Player to mirror image
 */
void player_mirror_image(player* p1);

/**
 * @brief Destructs player "object"
 *
 * @param p1 Player
 */
void player_destruct(player *p1);

#endif /*__PLAYER_SHIP_H*/
