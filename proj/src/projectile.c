#include "projectile.h"

void projectile_list_init(){
	if( (projectiles = (projectile_list *)malloc(sizeof(projectile_list))) == NULL)
		return;

	projectile_img = bitmap_load("projectile.bmp");

	projectiles->head = NULL;
	return;
}


int projectile_init(struct _player* p, unsigned short x, unsigned short y, int velocity) {

	projectile *proj = NULL;

	if((proj = (projectile *)malloc(sizeof(projectile))) == NULL)
		return 1;

	proj->x = x - (PROJECTILE_WIDTH/2);
	proj->y = y;
	proj->width = PROJECTILE_WIDTH;
	proj->height = PROJECTILE_HEIGHT;
	proj->velocity = velocity;
	proj->next = NULL;
	proj->prev = NULL;
	proj->shooter = p;

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
	//vg_draw_frame(proj->x, proj->y, proj->width, proj->height, rgb(0xFF0000));
	bitmap_draw(projectile_img, proj->x, proj->y, ALIGN_LEFT);

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
	return 1;
}

int collision(projectile* proj, unsigned char color, unsigned short x, unsigned short y) {
	projectile_delete(proj);
	return 1;
}

int projectile_reached_end(projectile *proj){
	return (proj->y < END_AT_TOP || proj->y > END_AT_BOTTOM);
}

void projectile_list_destruct() {
	bitmap_delete(projectile_img);

	projectile* iterator = projectiles->head;

	if(iterator == NULL)
		return;

	while(iterator->next != NULL){
		iterator = iterator->next;
		//free(iterator->prev); //crashes here
	}

	//free(projectiles); //crashes here
}
