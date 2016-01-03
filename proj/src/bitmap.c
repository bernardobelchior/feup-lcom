#include "bitmap.h"

bitmap* bitmap_load(const char* filename) {
	// allocating necessary size
	bitmap* bmp = (bitmap*) malloc(sizeof(bitmap));

	//sets the filepath
	char* filepath = (char*) malloc((strlen(res_path)+strlen(filename))*sizeof(char));
	strcpy(filepath, res_path);
	strcat(filepath, filename);

	// open filename in read binary mode
	FILE *image;
	//filepath = "/home/proj/res/ufo.bmp";
	image = fopen(filepath, "rb");
	if (image == NULL)
		return NULL;

	// read the bitmap file header
	bitmap_file_header bmp_file_header;
	fread(&bmp_file_header.type, sizeof(unsigned short), 1, image);

	// verify that this is a bmp file by check bitmap id
	if (bmp_file_header.type != 0x4D42) {
		fclose(image);
		return NULL;
	}

	int rd;
	do {
		if ((rd = fread(&bmp_file_header.size, sizeof(unsigned int), 1, image)) != 1)
			break;
		if ((rd = fread(&bmp_file_header.reserved, sizeof(unsigned int), 1, image)) != 1)
			break;
		if ((rd = fread(&bmp_file_header.offset, sizeof(unsigned int), 1, image)) != 1)
			break;
	} while (0);

	if (rd = !1) {
		fprintf(stderr, "Error reading image.\n");
		leave();
	}

	// read the bitmap info header
	bitmap_info_header bmp_info_header;
	fread(&bmp_info_header, sizeof(bitmap_info_header), 1, image);

	// move file pointer to the beginning of bitmap data
	fseek(image, bmp_file_header.offset, SEEK_SET);

	// allocate enough memory for the bitmap image data
	unsigned short* bitmap_image = (unsigned short*) malloc(bmp_info_header.image_size*sizeof(unsigned short));

	// verify memory allocation
	if (!bitmap_image) {
		free(bitmap_image);
		fclose(image);
		return NULL;
	}

	// read the bitmap image data and invert its content as it is stored with lines inverted horizontally
	//bmp uses 32-bit padding, so if the image has odd width, the last byte will be garbage.
	//in order to solve it, the last byte must be ignored if the image width is not even
	unsigned short i;
	unsigned short width = bmp_info_header.width;
	unsigned short height = bmp_info_header.height;
	if(width % 2 == 0){
		for (i = 1; i <= height; i++) {
			fread(bitmap_image + (height - i) * width, sizeof(unsigned short), width, image);
		}
	} else {
		unsigned short garbage;
		for (i = 1; i <= height; i++) {
			fread(bitmap_image + (height - i) * width, sizeof(unsigned short), width, image);
			fread(&garbage, 1, sizeof(unsigned short), image); //garbage pixel due to 32-bit padding
		}
	}

	// make sure bitmap image data was read
	if (bitmap_image == NULL) {
		fclose(image);
		return NULL;
	}

	// close file and return bitmap image data
	fclose(image);

	bmp->bmp_data = bitmap_image;
	bmp->bmp_info_header = bmp_info_header;

	return bmp;
}

void bitmap_mirror_horizontally(bitmap* bmp){
	unsigned short height = bmp->bmp_info_header.height;
	unsigned short width = bmp->bmp_info_header.width;

	unsigned short i;
	unsigned short* line = (unsigned short*) malloc(width*sizeof(unsigned short));
	for(i = 0; i < height; i++){
		memcpy(line, bmp->bmp_data + i*width, width*sizeof(unsigned short));
		memcpy(bmp->bmp_data + i*width, bmp->bmp_data + width*(height-i-1), width*sizeof(unsigned short));
		memcpy(bmp->bmp_data + width*(height-i-1), line, width*sizeof(unsigned short));
	}

	free(line);
}

void bitmap_draw(bitmap* bmp, short x, short y, Alignment alignment) {
	if (bmp == NULL)
		return;

	unsigned short width = bmp->bmp_info_header.width;
	unsigned short height = bmp->bmp_info_header.height;

	if (alignment == ALIGN_CENTER)
		x -= width / 2;
	else if (alignment == ALIGN_RIGHT)
		x -= width;

	vg_draw_pixmap(bmp->bmp_data, x, y, width, height);
}

void bitmap_delete(bitmap* bmp) {
	if (bmp == NULL)
		return;

	free(bmp->bmp_data);
	free(bmp);
}
