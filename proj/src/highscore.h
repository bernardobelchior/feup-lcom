#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "proj.h"
#include "state.h"
#include "rtc.h"

/** @defgroup highscore highscore
 * @{
 * highscore
 */

#define MAX_NUMBER_OF_SCORES 10

typedef struct{
	char* name;
	Date* date;
	unsigned int points;
} score;

static char highscore_path[] = "/home/proj/cfg/highscore.txt";
static score** highscores;
static unsigned char highscore_size;
menu* highscore_menu;
extern font* space_invaders_font;

/**
 * @brief initializes the information referring to the highscores
 */
void highscore_init();

/**
 * @brief Reads the highscores stored on a file
 *
 * @param file file which contains the current highscores
 */
score* highscore_read(FILE* file);

/**
 * @brief adds a new highscore to the highscore file
 *
 * @param name name of the player
 * @param date date on which the highscore was achieved
 * @param points points achieved
 */
int highscore_add(char* name, Date* date, unsigned int points);

/**
 * @brief writes a new highscore on the highscore file
 */
int highscore_write(FILE* file, score* sc);

/**
 * @brief checks if a certain number of points are a new highscore
 */
int is_on_highscores(unsigned int points);

/**
 * @brief keeps and updates (if necessary) the display of the highscore menu
 */
void highscore_tick();

/**
 * @brief goes back to the main menu
 */
void highscore_back_on_click();


/**
 * @brief deletes the information relative to the highscores
 */
void highscore_destruct();



#endif
