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

void fifo_print(fifo *f1){

	printf("\t");
	while(!fifo_is_empty(f1)){
		printf("%c",fifo_top(f1));
		if(fifo_pop(f1) != 0)
			break;
	}

	printf("\n");

}

char fifo_top(fifo *f1){
	if(f1 == NULL || f1->front == NULL)
		return 0;

	return *(f1->front->word);
}

int fifo_pop(fifo *f1){
	if (f1 == NULL || f1->front == NULL)
		return 1;

	fifo_element *temp = f1->front;
	f1->front = f1->front->next;
	free(temp);
	if(f1->front == NULL)
	return 0;
}

int fifo_push(fifo *f1,char word){
	if(f1 == NULL)
		return 1;

	fifo_element *novo = new_element(word);

	if(fifo_is_empty(f1))
		f1->front = novo;

	fifo_element *iterator = f1->front;

	while(iterator->next != NULL)
		iterator=iterator->next;

	iterator->next = novo;

	novo->next = NULL;
	return 0;
}

int fifo_delete(fifo *f1){

	if(f1 == NULL)
		return 1;

	while(!fifo_is_empty(f1))
		fifo_pop(f1);

	f1 = NULL;

	return  0;
}
