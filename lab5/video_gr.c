#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"
#include "timer.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000 
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xF0000000
#define H_RES             1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem; /* Process address to which VRAM is mapped */

static unsigned h_res; /* Horizontal screen resolution in pixels */
static unsigned v_res; /* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void *vg_init(unsigned short mode) {
	vbe_mode_info_t info;
	struct reg86u reg86;

	reg86.u.b.intno = BIOS_VIDEO_INT; /* BIOS video services */
	reg86.u.w.ax = SET_VBE_MODE; /* Set Video Mode function */
	reg86.u.w.bx = SET_LINEAR_MODE | mode; /* Mode */

	if ((video_mem = lm_init()) == NULL) {
		printf("\tvg_init(): lm_init() failed \n");
		return NULL;
	}

	if (sys_int86(&reg86) != OK) { // Sets video mode
		printf("\tvg_init(): sys_int86() failed \n");
		return NULL;
	}

	/*if(vbe_get_mode_info(mode, &info) != 0 ){ // Gets info
		printf("\tvg_init(): vbe_get_mode_info() failed \n");
		return NULL;
	}

	h_res = info.XResolution;
	v_res = info.YResolution; //Sets global variables
	bits_per_pixel = info.BitsPerPixel;*/

	h_res = H_RES;
	v_res = V_RES; //temporary until the function get_mode_info is done
	bits_per_pixel = BITS_PER_PIXEL;
	video_mem = VRAM_PHYS_ADDR;

	return video_mem;
}

int vg_draw_rectangle(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned long color){
	unsigned int i;
	unsigned int j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			*(video_mem + i*h_res + j) = 0x15;
		}
	}

	return 0;
}

int vg_exit() {
	struct reg86u reg86;

	reg86.u.b.intno = 0x10; /* BIOS video services */

	reg86.u.b.ah = 0x00; /* Set Video Mode function */
	reg86.u.b.al = 0x03; /* 80x25 text mode*/

	if (sys_int86(&reg86) != OK) {
		printf("\tvg_exit(): sys_int86() failed \n");
		return 1;
	} else
		return 0;
}
