#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>

typedef struct _fifo_element {
	struct _fifo_element *next;
	char *word;
} fifo_element;

typedef struct	{
	fifo_element *front;
} fifo;

fifo* fifo_init();
fifo_element *new_element(char word);
int fifo_is_empty(fifo *f1);
void fifo_print(fifo *f1);
char fifo_top(fifo *f1);
int fifo_pop(fifo *f1);
int fifo_push(fifo *f1, char word);
int fifo_delete(fifo *f1);

#endif
