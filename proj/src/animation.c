#include "animation.h"


animation* animation_init(){
	animation* a = (animation*) malloc(sizeof(animation));

	a->head = NULL;
	a->current = NULL;

	return a;
}

void animation_add_by_filename(animation* a, const char* filename){
	sprite* sp = (sprite*) malloc(sizeof(sprite));
	sp->bmp = bitmap_load(filename);
	sp->delete_on_destruct = 1;

	if(a->head == NULL){
		a->head = sp;
		sp->next = sp;
		a->current = sp;
	}
	else{
		sprite* it = a->head;
		while(it->next != a->head){
			it = it->next;
		}
		it->next = sp;
		sp->next = a->head;
	}

}

void animation_add_by_bmp(animation* a, bitmap* bmp){
	sprite* sp = (sprite*) malloc(sizeof(sprite));
	sp->bmp = bmp;
	sp->delete_on_destruct = 0;

	if(a->head == NULL){
		a->head = sp;
		sp->next = sp;
		a->current = sp;
	}
	else{
		sprite* it = a->head;
		while(it->next != a->head){
			it = it->next;
		}
		it->next = sp;
		sp->next = a->head;
	}
}

void animation_next(animation* a){
	a->current = a->current->next;
}

void animation_destruct(animation* a){
	if(a->head == NULL)
		return;

	sprite* it = a->head->next;
	sprite* next;

	a->head->next = NULL;

	if(it == a->head){
		free(a->head);
		return;
	}

	while(it != NULL){
		next = it->next;
		if(it->delete_on_destruct)
			bitmap_delete(it->bmp);
		free(it);
		it = next;
	}

	//free(a); //crashes here
}
