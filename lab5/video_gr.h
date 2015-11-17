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

 /** @} end of video_gr */
 
#endif /* __VIDEO_GR_H */
