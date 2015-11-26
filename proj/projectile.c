#include "projectile.h"

Projectile *projectile_init() {

	Projectile *proj1 = (Projectile *) malloc(sizeof(Projectile));

	proj1->xpos = x;
	proj1->ypos = y;
	//proj1->velocity = TODO
	//inicializar mem pos
}

int projectile_draw(Projectile *proj) {
	//desenha projetil

	return 1;
}

int delete_projectile(Projectile *proj){
	free(proj);
}

int move_projectile(Projectile *proj) {

	//if (cor do proximo pixel != cor do alien ou jogador ou escudo
	//faz projectile_draw na posicao x+velocity;

	//senao, lanca collision

	return 1;
}

int collision(Projectile* proj, unsigned char color, unsigned short x, unsigned short y) {
	//verifica qual a cor do objeto atingido, e lanca a funcao apropriada

	delete_projectile(proj);
	return 1;
}

int alien_collision(unsigned short x, unsigned short y){
	//procura na lista de aliens qual o alien que esta na posicao x,y
	//lanca alien_hit para o alien em questao

	return 1;
}

int shield_collision(unsigned short x, unsigned short y){
	//procura na lista de shields qual o shield que esta na posicao x,y
		//lanca shield_hit para o shields em questao

	return 1;
}


