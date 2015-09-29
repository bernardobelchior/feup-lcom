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

	unsigned int i,j;
	for(i = 0; i < scr_lines; i++){
	  for(j = 0; j < scr_width; j++){
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
  
	if(r >= scr_lines || c >= scr_width || r < 0 || c < 0)
		return -1;

	char* vptr = video_mem + 2*r*scr_width + 2*c;

	*vptr = ch;
	vptr++;
	*vptr = attr;
	return 0;
}

int vt_print_string(char* str, char attr, int r, int c) {

	if(str == NULL || r < 0 || c < 0 || r*scr_width+c+strlen(str) > scr_width*scr_lines)
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

  char* str = (char*) malloc(10);

  sprintf(str, "%d", num);

  vt_print_string(str, attr, r, c);
}


int vt_draw_frame(int width, int height, char attr, int r, int c) {

	if(r+height > scr_lines || c+width > scr_width || c < 0 || r < 0 || width < 0 || height < 0)
		return -1;

	vt_print_char(0xC9,attr, r, c);

	unsigned i;
  for(i = 1; i < width-1; i++){
	  vt_print_char(0xCD, attr, r, c+i);
  }

  vt_print_char(0xBB, attr, r, c+width-1);


  for(i = 0; i < height - 2; i++){
	  vt_print_char(0xBA, attr, r+1+i, c);
	  vt_print_char(0xBA, attr, r+1+i, c+width-1);
  }

  vt_print_char(0xC8, attr, r+height-1, c);

  for(i = 1; i < width-1; i++){
  	  vt_print_char(0xCD, attr, r+height-1, c+i);
    }

  vt_print_char(0xBC, attr, r+height-1, c+width-1);
  return 0;
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
