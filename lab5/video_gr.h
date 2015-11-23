#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 * 
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen, 
 *  and the number of colors
 * 
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 * 
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

/**
* @brief Draws a frame starting on (x,y) with specified width, height and color
*
* @param x x
* @param y y
* @param width Frame width
* @param height Frame height
* @param color Frame color
*
* @return 0 upon success, non-zero upon failure
*/
int vg_draw_frame(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned long color);

/**
 * @brief Draws a line starting at (xi,yi) and ending at (xf,yf)
 *
 * @param xi Initial x position
 * @param yi Initial y position
 * @param xf Final x position
 * @param yf Final y position
 * @param color Line color
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color);

/**
 * @brief Draws a pixmap on position (xi,yi)
 *
 * @param xi Pixmap x position
 * @param yi Pixmap y position
 * @param pixmap Pixmap to draw
 */
char vg_draw_pixmap(unsigned short xi, unsigned short yi, unsigned short width, unsigned short height, char *pixmap);

/**
 * @brief Draws xpm on position (xi,yi). Converts xpm to pixmap and calls draw_pixmap.
 *
 * @param xi xpm x position
 * @param yi xpm y position
 * @param xpm xpm to draw
 */
char vg_draw_xpm(unsigned short xi, unsigned short yi, char *xpm[]);

/**
 * @brief clears section of the screen where the xpm is located
 */
//int vg_destroy_pixmap(unsigned short xi, unsigned short yi,char *xpm[]);

/**
 * @brief Moves a pixmap vertically or horizontally
 *
 * @parax xi initial x position
 * @param yi initial y position
 * @param xpm xpm to move
 * @param hor 0 if vertical movement, 1 if horizontal movement
 * @param delta distance in pixels to move
 * @param time time for the movement to be completed
 */
int vg_move_pixmap(unsigned short xi, unsigned short yi, unsigned short width, unsigned short height, char *pixmap,
		unsigned short hor, float next_position);

/**
 * @brief Clear screen by setting all pixels to black
 */
void vg_clear_screen();

/**
 * @brief Updates screen by bringing double buffer to the screen, and clear the double buffer.
 *
 * @return Returns 0 on success and non-zero otherwise.
 */
int vg_update_screen();

 /** @} end of video_gr */
 
#endif /* __VIDEO_GR_H */
