#ifndef SHIELD_H
#define SHIELD_H

#define SHIELD_WIDTH 10
#define SHIELD_HEIGHT 10
#define SHIELD_DURABILITY 10

typedef struct{
	int durability;
	unsigned int xpos, ypos;
	char *mem_pos;
} shield;

typedef struct{
	//TODO
	unsigned short xpos, ypos;
	unsigned char durability;
	char *mem_pos;
} shield_sprite;

//int shield_init
#endif
