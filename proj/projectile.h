#ifndef PROJECTILE_H
#define PROJECTILE_H

typedef struct{
	unsigned int xpos ,ypos;
	int velocity;
	char *mem_pos;
} Projectile;

int projectile_init(int xpos); //initializes the projectile
int projectile_draw();
int move_projectile();
int collision(char color); //checks what kind of target was hit and throws the appropriate destruction event
int alien_collision();
int player_collision();
int shield_collision();
int delete_projectile(Projectile *proj);

#endif
