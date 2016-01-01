#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"
#include "timer.h"
#include "video_gr.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */

/* Private global variables */

static unsigned short *video_mem; /* Process address to which VRAM is mapped */

void *vg_init(unsigned short mode) {
	vbe_mode_info_t info;
	struct reg86u reg86;
	int r;
	struct mem_range mr;

	reg86.u.b.intno = BIOS_VIDEO_INT; /* BIOS video services */
	reg86.u.w.ax = SET_VBE_MODE; /* Set Video Mode function */
	reg86.u.w.bx = SET_LINEAR_MODE | mode; /* Mode */

	if (sys_int86(&reg86) != OK) { // Sets video mode
		printf("\tvg_init(): sys_int86() failed \n");
		return NULL;
	}

	switch (reg86.u.w.ax) {
	case VBE_FUNC_CALL_FAILED:
		printf("\tvg_init(): sys_int86() function call failed.\n");
		return NULL;
		break;
	case VBE_FUNC_NOT_SUPPORTED:
		printf("\tvg_init(): sys_int86() function not supported.\n");
		return NULL;
		break;
	case VBE_FUNC_INVALID_CUR_MODE:
		printf(
				"\tvg_init(): sys_int86() function invalid in current video mode.\n");
		return NULL;
		break;
	}

	if (lm_init() == NULL) {
		printf("\tvg_init(): lm_init() failed \n");
		return NULL;
	}

	if (vbe_get_mode_info(mode, &info) != OK) { // Gets info
		printf("\tvg_init(): vbe_get_mode_info() failed \n");
		return NULL;
	}

	h_res = info.XResolution;
	v_res = info.YResolution; //Sets global variables
	bits_per_pixel = info.BitsPerPixel;

	//Allow memory mapping

	mr.mr_base = (phys_bytes)(info.PhysBasePtr);
	mr.mr_limit = mr.mr_base
			+ info.XResolution * info.YResolution * info.BitsPerPixel / 8;

	if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	// Map memory

	video_mem = vm_map_phys(SELF, (void *) mr.mr_base,
			info.XResolution * info.YResolution * info.BitsPerPixel / 8);

	double_buffer = malloc(h_res * v_res * bits_per_pixel/8);

	/*if(video_mem == MAP_FAILED)
	 panic("video_txt couldn't map video memory");*/

	return video_mem;
}

char vg_set_pixel(short x, short y, unsigned short color) {
	if (x < 0)
		return 1;
	else if (x >= h_res)
		return 2;

	if (y < 0)
		return 3;
	else if (y >= v_res)
		return 4;

	if(color == TRANSPARENCY_COLOR)
		return 5;

	*(double_buffer + y * h_res + x) = color;

	return 0;
}


int vg_draw_frame(unsigned short x, unsigned short y, unsigned short width,
		unsigned short height, unsigned short color) {
	unsigned int i;

	//Prints first line
	for (i = 0; i < width; i++) {
		vg_set_pixel_asm(x + i, y, color);
	}

	//Prints vertical lines
	for (i = 1; i < height - 1; i++) {
		vg_set_pixel_asm(x, y + i, color);
		vg_set_pixel_asm(x + width - 1, y + i, color);
	}

	//Prints last line
	for (i = 0; i < width; i++) {
		vg_set_pixel_asm(x + i, y + height - 1, color);
	}

	return 0;
}

unsigned short get_v_res(){
	return v_res;
}

unsigned short get_h_res(){
	return h_res;
}

unsigned short get_bits_per_pixel(){
	return bits_per_pixel;
}

int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned short color) {
	short* vmem = double_buffer;

	if (xi == xf) {
		unsigned int i;
		for (i = 0; i < yf - yi; i++) {
			vg_set_pixel(xi, yi + i, color);
		}
	} else if (yi == yf) {
		unsigned int i;
		for (i = 0; i < xf - xi; i++) {
			vg_set_pixel(xi + i, yi, color);
		}
	} else {
		unsigned int offset = 0;
		float m = ((double) (yf - yi)) / (xf - xi);
		if (m < 0)
			offset = 1;

		if (m > -1 && m < 1) {
			int i;
			for (i = xi; i <= xf; i++) {
				vg_set_pixel(i, offset * yi + (int) (m * i), color);
			}
		} else {
			int i;
			for (i = yi; i <= yf; i++) {
				vg_set_pixel(offset * xi + (int) (i / m), i, color);
			}
		}
	}

	return 0;
}

void vg_clear_screen() {
	memset(double_buffer, 0, v_res*h_res*bits_per_pixel/8);
}

int vg_update_screen() {
	if (double_buffer == NULL)
		return 1;

	memcpy(video_mem, double_buffer, h_res * v_res * bits_per_pixel/8);

	vg_clear_screen();

	return 0;
}

void* vg_get_double_buffer(){
	return double_buffer;
}

int vg_exit() {
	struct reg86u reg86;

	free(double_buffer);

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00; /* Set Video Mode function */
	reg86.u.b.al = 0x03; /* 80x25 text mode*/

	if (sys_int86(&reg86) != OK) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}

unsigned short rgb(unsigned long color){
	unsigned short red, green, blue;
	red = (color & 0x00FF0000) >> 16;
	green = (color & 0x0000FF00) >> 8;
	blue = color & 0x000000FF;

	red = red * 31 / 255;
	green = green * 63 / 255;
	blue = blue * 31 / 255;

	return (red << 11) | (green << 5) | blue;
}

short* vg_set_line(unsigned short x, unsigned short y, unsigned short width, unsigned short* line){
	return memcpy(double_buffer+y*h_res+x, line, width*sizeof(unsigned short));
}

char vg_draw_pixmap(unsigned short* pixmap, short x, short y, unsigned short width, unsigned short height) {
	if (x + width < 0 || y + height < 0 || x > h_res || y > v_res)
		return 1;

	unsigned short i, j;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			vg_set_pixel(x+j, y+i, *(pixmap+i*width+j));

	return 0;
}
