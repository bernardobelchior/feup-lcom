#ifndef PROJECTILE_H
#define PROJECTILE_H

typedef struct{
	unsigned short xpos ,ypos;
	int velocity;
	unsigned char *mem_pos;
} Projectile;

Projectile* projectile_init(unsigned short x, unsigned short y); //initializes the projectile

int projectile_draw(Projectile *proj);
int delete_projectile(Projectile *proj);
int move_projectile(Projectile *proj);
int collision(unsigned char color, unsigned short x, unsigned short y); //checks what kind of target was hit and throws the appropriate destruction event
int alien_collision(unsigned short x, unsigned short y);
int player_collision();
int shield_collision(unsigned short x, unsigned short y);


#endif
