#include <minix/drivers.h>
#include <sys/video.h>
#include <sys/mman.h>
#include <string.h>
#include <assert.h>

#include "vt_info.h"

#include "video_txt.h"

/* Private global variables */

static char *video_mem;		/* Address to which VRAM is mapped */

static unsigned scr_width;	/* Width of screen in columns */
static unsigned scr_lines;	/* Height of screen in lines */

void vt_fill(char ch, char attr) {
  
	char* vptr = video_mem;

	for(unsigned int i = 0; i < scr_lines; i++){
	  for(unsigned int j = 0; j < scr_width; j++){
		 *vptr = ch;
		 vptr++;
		 *vptr = attr;
		 vptr++;
	  }
	}
  
}

void vt_blank() {
	vt_fill(' ', 15);
}

int vt_print_char(char ch, char attr, int r, int c) {
  
	/*if(r > scr_lines || c > scr_width)
		return -1;*/

	char* vptr = video_mem;

	vptr = vptr + 2*r*scr_width + 2*c;

	*vptr = ch;
	vptr++;
	*vptr = attr;
	return 0;
}

int vt_print_string(char* str, char attr, int r, int c) {

	if(str == NULL)
		return -1;

	char *vptr = video_mem;

	vptr = vptr + 2*r*scr_width + 2*c;

	while(*str != '\0'){
		*vptr = *str;
		vptr++;
		str++;
		*vptr = attr;
		vptr++;
	}
}

int vt_print_int(int num, char attr, int r, int c) {

  char[] str;
  itoa(num, *str, 10);

  vt_print_string(*str, attr, r, c);
}


int vt_draw_frame(int width, int height, char attr, int r, int c) {

  char* vptr = video_mem;

  vptr = vptr + 2*r*scr_width + 2*c;

  unsigned i;
  for(i = 0; i < width; i++){
	  *vptr = ' ';
	  vptr++;
	  *vptr = attr;
	  vptr++;
  }


  for(i = 0; i < height - 2; i++){
	  vptr = video_mem + 2*r*scr_width + 2*c + 2*scr_width*(1+i);
	  *vptr = ' ';
	  vptr++;
	  *vptr = attr;
	  vptr++;
	  vptr += 2*width-2;
	  *vptr = ' ';
	  vptr++;
	  *vptr = attr;
  }

  vptr = video_mem + 2*(r+height)*scr_width + 2*c;

  for(i = 0; i < width; i++){
  	  *vptr = ' ';
  	  vptr++;
  	  *vptr = attr;
  	  vptr++;
    }
}

/*
 * THIS FUNCTION IS FINALIZED, do NOT touch it
 */

char *vt_init(vt_info_t *vi_p) {

  int r;
  struct mem_range mr;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes)(vi_p->vram_base);
  mr.mr_limit = mr.mr_base + vi_p->vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	  panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vi_p->vram_size);

  if(video_mem == MAP_FAILED)
	  panic("video_txt couldn't map video memory");

  /* Save text mode resolution */

  scr_lines = vi_p->scr_lines;
  scr_width = vi_p->scr_width;

  return video_mem;
}
