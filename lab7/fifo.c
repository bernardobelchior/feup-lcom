#include "fifo.h"

fifo *fifo_init(){
	fifo* nova = (fifo *) malloc (sizeof(fifo));
	nova->front = NULL;
}

fifo_element *new_element(char word){
	char *content;
	fifo_element *novo = (fifo_element *)malloc(sizeof(fifo_element));
	novo->next = NULL;
	content = (char *)malloc(sizeof(word));
	*content = word;
	novo->word = content;

	return novo;
}
int fifo_is_empty(fifo *f1){
	return (f1->front == NULL);
}

char fifo_top(fifo *f1){
	if(f1 == NULL || f1->front == NULL)
		return 0;

	return *(f1->front->word);
}

int fifo_pop(fifo *f1){
	if (f1 == NULL || f1->front == NULL)
		return 1;

	free(f1->front);
	return 0;
}

int fifo_push(fifo *f1,fifo_element *fe1){
	if(f1 == NULL)
		return 1;

	if(fifo_is_empty(f1))
		f1->front = fe1;

	fifo_element *iterator = f1->front;

	while(iterator->next != NULL)
		iterator=iterator->next;

	iterator->next = fe1;
}

int fifo_delete(fifo *f1){

	if(f1 == NULL)
		return 1;

	while(!fifo_is_empty(f1))
		fifo_pop(f1);

	f1 = NULL;
}
