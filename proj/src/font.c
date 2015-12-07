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
	
	return f;
}


void font_draw_string(font* f, unsigned short x, unsigned short y, const char* str){
	unsigned short i = 0;
	unsigned short* letter_position;
	while(str[i] != '\0'){
		if(str[i] >= f->lower_limit && str[i] <= f->higher_limit){
			letter_position = f->letters->bmp_data + ((str[i]-f->lower_limit)%f->letters_per_line)*LETTER_HEIGHT*LETTER_WIDTH + (str[i]-f->lower_limit)*LETTER_WIDTH;
			vg_draw_pixmap(letter_position, x+LETTER_WIDTH*i, y, LETTER_WIDTH, LETTER_HEIGHT);//, ALIGN_LEFT);
		}	
		i++;
	}
}

void font_delete(font* f){
	bitmap_delete(f->letters);
	free(f);
}
