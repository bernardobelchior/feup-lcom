#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

#define TRANSPARENCY_COLOR (63 << 5)

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

unsigned short* double_buffer;
unsigned h_res; /* Horizontal screen resolution in pixels */
unsigned v_res; /* Vertical screen resolution in pixels */
unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

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

unsigned short get_v_res();
unsigned short get_h_res();

/**
 * @brief Sets the pixel in the (x,y) to the color passed as argument
 *
 * @param x Position of the pixel in the x axis
 * @param y Position of the pixel in the y axis
 * @param color Color to color the pixel with
 *
 * @return Returns 0 on sucess. Returns 1 if x < 0; 2 if x >= h_res; 3 if y < 0; 4 if y >= v_res. Returns 5 if the color is considered transparent.
 */
char vg_set_pixel(short x, short y, unsigned short color);

/**
 * @brief Copies an entire line to double buffer
 *
 * @param y Position of the line in the y axis
 * @param line Pointer to line to copy
 *
 * @return Returns pointer to line destination.
 */
short* vg_set_line(unsigned short x, unsigned short y, unsigned short width, unsigned short* line);

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
int vg_draw_frame(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned short color);

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
int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned short color);

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

/**
 * @brief Returns double buffer pointer.
 */
void *vg_get_double_buffer();

/**
 * @brief Gets vertical resolution
 *
 * @return Returns vertical resolution
 */
unsigned short get_v_res();

/**
 * @brief Gets horizontal resolution
 *
 * @return Returns horizontal resolution
 */
unsigned short get_h_res();

/**
 * @brief Gets bits per pixel
 *
 * @return Returns bits per pixel
 */
unsigned short get_bits_per_pixel();

/**
 * @brief Converts a 8:8:8 RGB color to a 5:6:5 one.
 *
 * @return Returns the converted color
 */
unsigned short rgb(unsigned long color);

/**
 * @brief Draws pixmap
 *
 * @param x Position in the x axis
 * @param y Position in the y axis
 * @param width Pixmap width
 * @param height Pixmap height
 * @param pixmap Pointer to pixmap
 */
char vg_draw_pixmap(unsigned short* pixmap, short x, short y, unsigned short width, unsigned short height);

 /** @} end of video_gr */
 
#endif /* __VIDEO_GR_H */
