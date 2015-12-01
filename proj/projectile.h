#ifndef PROJECTILE_H
#define PROJECTILE_H

#define END_AT_TOP 50
#define END_AT_BOTTOM 700

typedef struct{
	unsigned short x ,y;
	int velocity;
	unsigned char *mem_pos;
} projectile;

projectile* projectile_init(unsigned short x, unsigned short y, int velocity); //initializes the projectile
int projectile_draw(projectile *proj);
int projectile_delete(projectile *proj);
int projectile_move(projectile *proj);
int collision(projectile* proj, unsigned char color, unsigned short x, unsigned short y); //checks what kind of target was hit and throws the appropriate destruction event
int alien_collision(unsigned short x, unsigned short y);
int player_collision();
int shield_collision(unsigned short x, unsigned short y);
int projectile_reached_end(projectile *proj);

#endif
