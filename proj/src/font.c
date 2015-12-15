#include "font.h"

font* font_init(const char* font_name){
	font* f = (font*) malloc(sizeof(font));
	f->lower_limit = 32;
	f->higher_limit = 126;
	f->letters_per_line = 10;

	unsigned char* full_path =  (unsigned char*) malloc((strlen(font_path) + strlen(font_name))*sizeof(unsigned char));

	strcpy(full_path, font_path);
	strcat(full_path, font_name);

	if((f->letters = bitmap_load(full_path)) == NULL){
		free(f);
		return NULL;
	}

	font_recolor(f, rgb(0x000000), rgb(0xFFFFFF));

	return f;
}

void font_recolor(font* f, unsigned short initial_color, unsigned short final_color){
	unsigned short i, j, width = f->letters->bmp_info_header.width, height = f->letters->bmp_info_header.height;

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			if(*(f->letters->bmp_data + j + i*width) == initial_color)
				*(f->letters->bmp_data + j + i*width) = final_color;
		}
	}
}

void font_draw_string(font* f, short x, short y, const char* str, Alignment alignment){
	unsigned short width = f->letters->bmp_info_header.width;
	unsigned short height = f->letters->bmp_info_header.height;
	unsigned short i, j, k;
	unsigned short *letter_position;

	if(alignment == ALIGN_CENTER)
		x -= (unsigned short) ((LETTER_WIDTH*strlen(str))/2);
	else if(alignment == ALIGN_RIGHT)
		x -= LETTER_WIDTH*strlen(str);

	//prints the string

	while(str[i] != '\0'){
		if(str[i] > f->lower_limit && str[i] < f->higher_limit){ //if the char is valid, print it, otherwise do nothing
			letter_position = f->letters->bmp_data + ((str[i] - f->lower_limit) / f->letters_per_line)*width*LETTER_HEIGHT + ((str[i] - f->lower_limit) % f->letters_per_line)*LETTER_WIDTH;
			for(j = 0; j < LETTER_HEIGHT; j++){
				for(k = 0; k < LETTER_WIDTH; k++){
					vg_set_pixel(x+k+i*LETTER_WIDTH, y+j, *(letter_position + j*width + k));
				}
			}
		}
		i++;
	}




	//vg_draw_pixmap(f->letters->bmp_data, x, y, LETTER_WIDTH, LETTER_HEIGHT);
}

void font_delete(font* f){
	bitmap_delete(f->letters);
	free(f);
}
