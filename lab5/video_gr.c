#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"
#include "timer.h"
#include "read_xpm.h"

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
	int r;
	struct mem_range mr;

	reg86.u.b.intno = BIOS_VIDEO_INT; /* BIOS video services */
	reg86.u.w.ax = SET_VBE_MODE; /* Set Video Mode function */
	reg86.u.w.bx = SET_LINEAR_MODE | mode; /* Mode */

	if (sys_int86(&reg86) != OK) { // Sets video mode
		printf("\tvg_init(): sys_int86() failed \n");
		return NULL;
	}

	switch(reg86.u.w.ax){
	case VBE_FUNC_CALL_FAILED:
		printf("\tvg_init(): sys_int86() function call failed.\n");
		return NULL;
		break;
	case VBE_FUNC_NOT_SUPPORTED:
		printf("\tvg_init(): sys_int86() function not supported.\n");
		return NULL;
		break;
	case VBE_FUNC_INVALID_CUR_MODE:
		printf("\tvg_init(): sys_int86() function invalid in current video mode.\n");
		return NULL;
		break;
	}

	if (lm_init() == NULL) {
		printf("\tvg_init(): lm_init() failed \n");
		return NULL;
	}

	if(vbe_get_mode_info(mode, &info) != OK ){ // Gets info
		printf("\tvg_init(): vbe_get_mode_info() failed \n");
		return NULL;
	}

	//Allow memory mapping

	mr.mr_base = (phys_bytes)(info.PhysBasePtr);
	mr.mr_limit = mr.mr_base + info.XResolution*info.YResolution*info.BitsPerPixel/8;

	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
		panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

	// Map memory

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, info.XResolution*info.YResolution*info.BitsPerPixel/8);

	/*if(video_mem == MAP_FAILED)
		panic("video_txt couldn't map video memory");*/

	h_res = info.XResolution;
	v_res = info.YResolution; //Sets global variables
	bits_per_pixel = info.BitsPerPixel;

	return video_mem;
}

int vg_draw_frame(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned long color){
	char* vmem = video_mem;
	vmem += y * h_res + x;

	unsigned int i;

	//Prints first line
	for(i = 0; i < width; i++){
		*(vmem + i) = color;
	}

	//Prints vertical lines
	for(i = 1; i < height-1; i++){
		*(vmem + i*h_res) = color;
		*(vmem + i*h_res + width) = color;
	}

	//Prints last line
	for(i = 0; i < width; i++){
		*(vmem + h_res*(height-1) + i) = color;
	}

	return 0;
}

int vg_draw_line(unsigned short xi, unsigned short yi, unsigned short xf, unsigned short yf, unsigned long color){
	char* vmem = video_mem;

	if(xi == xf){
		unsigned int i;
		for(i = 0; i < yf-yi; i++){
			*(vmem + (yi+i)*h_res + xi) = color;
		}
	}
	else if(yi == yf){
		unsigned int i;
		for(i = 0; i < xf-xi; i++){
			*(vmem + i+xi + yi*h_res) = color;
		}
	}
	else{
		unsigned int offset = 0;
		float m = ((double)(yf-yi))/(xf-xi);
		if (m < 0)
			offset = 1;

		if (m > -1 && m < 1){
			int i;
			for(i = xi; i <= xf; i++){
				*(vmem + i + offset*yi*h_res + h_res*((int)(m*i))) = color;
			}
		}
		else {
			int i;
			for(i = yi; i <= yf; i++){
				*(vmem + i*h_res + offset*xi + (int) (i/m)) = color;
			}
		}
	}

	return 0;
}

char vg_draw_pixmap(unsigned short xi, unsigned short yi,  char *xpm[]){
	int width, height;
	char *pixmap;

	if((pixmap = read_xpm(xpm, &width, &height)) == NULL)
		return 1;

	if(xi + width > h_res || yi + height > v_res)
		return 1;

	unsigned short i, j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			*(video_mem + (yi+i)*h_res + (xi+j)) = *(pixmap + i*height + j);
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
