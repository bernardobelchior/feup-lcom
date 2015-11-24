#ifndef ALIENS_H
#define ALIENS_H

enum alien_type { small, medium, large, ufo};

typedef struct{
	int xpos, ypos;
	int velocity;
	char *mem_pos;
	int width, height;
	enum alien_type type;
} alien;

int alien_init(int xpos, int ypos, enum alien_type type);
int draw_alien();
int move_alien();
int alien_hit();

#endif
