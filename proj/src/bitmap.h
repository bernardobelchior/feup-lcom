#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>

/** @defgroup Bitmap Bitmap
 * @{
 * Functions for manipulating bitmaps
 */

struct font;

typedef enum {
    ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT
} Alignment;

typedef struct {
    unsigned short type; // specifies the file type
    unsigned int size; // specifies the size in bytes of the bitmap file
    unsigned int reserved; // reserved; must be 0
    unsigned int offset; // specifies the offset in bytes from the bitmapfileheader to the bitmap bits
} bitmap_file_header;

typedef struct {
    unsigned int size; // specifies the number of bytes required by the struct
    int width; // specifies width in pixels
    int height; // specifies height in pixels
    unsigned short planes; // specifies the number of color planes, must be 1
    unsigned short bits; // specifies the number of bit per pixel
    unsigned int compression; // specifies the type of compression
    unsigned int image_size; // size of image in bytes
    int h_res; // number of pixels per meter in x axis
    int v_res; // number of pixels per meter in y axis
    unsigned int number_of_colors; // number of colors used by the bitmap
    unsigned int important_colors; // number of colors that are important
} bitmap_info_header;

/// Represents a Bitmap
typedef struct {
    bitmap_info_header bmp_info_header;
    unsigned short* bmp_data;
} bitmap;

static char res_path[] = "/home/proj/res/";

/**
 * @brief loads a bitmap
 *
 * @ret bitmap struct
 */
bitmap* bitmap_load(const char* filename);

/**
 * @draws a bitmap on the screen
 *
 * @param bmp bitmap to draw
 * @param x x position to draw the bitmap
 * @param y y position to draw the bitmap
 * @param alignment alignment along the x axis
 */
void bitmap_draw(bitmap* bmp, short x, short y, Alignment alignment);

/**
 * @brief flips a bitmap along the x axis
 */
void bitmap_mirror_horizontally(bitmap* bmp);

/**
 * @brief deletes a bitmap
 */
void bitmap_delete(bitmap* bmp);

#endif
