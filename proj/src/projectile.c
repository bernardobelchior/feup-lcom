#include "projectile.h"


void projectile_list_init(){
	if( (projectiles = (projectile_list *)malloc(sizeof(projectile_list))) == NULL)
		return;

	projectiles->head = NULL;
	return;
}


int projectile_init(unsigned short x, unsigned short y, int velocity){

	projectile *proj = NULL;

	if((proj = (projectile *)malloc(sizeof(projectile))) == NULL)
		return 1;

	proj->x = x;
	proj->y = y;
	proj->velocity = velocity;
	proj->next = NULL;
	proj->prev = NULL;

	if(projectiles->head == NULL){
		projectiles->head = proj;
		return 0;
	}

	projectile *iterator = projectiles->head;

	while(iterator->next != NULL)
		iterator = iterator->next;

	proj->prev = iterator;
	iterator->next = proj;

	return 0;
}

int projectile_draw(projectile *proj) {
	vg_draw_frame(proj->x, proj->y, 5, 5, rgb(0xFF0000));

	return 1;
}

int projectile_delete(projectile *proj){

	projectile *iterator = projectiles->head;

	do{
		if(iterator == proj){

			if(proj->prev != NULL)
				proj->prev->next = proj->next;

			if(proj->next != NULL)
				proj->next->prev = proj->prev;

			if(projectiles->head == proj)
				projectiles->head = proj->next;

			free(proj);

			return 0;
		}

		iterator=iterator->next;
	}while(iterator != NULL);

	return 1;
}

int projectile_move(projectile *proj) {
	proj->y += proj->velocity;
	//if (cor do proximo pixel != cor do alien ou jogador ou escudo
	//faz projectile_draw na posicao x+velocity;

	//senao, lanca collision

	return 1;
}

int collision(projectile* proj, unsigned char color, unsigned short x, unsigned short y) {
	//verifica qual a cor do objeto atingido, e lanca a funcao apropriada

	projectile_delete(proj);
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

int projectile_reached_end(projectile *proj){
	return (proj->y < END_AT_TOP || proj->y > END_AT_BOTTOM);
}

