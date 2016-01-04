#ifndef FIFO_H
#define FIFO_H

#include <stdio.h>

/**
 * @brief node of the FIFO, contains a pointer to the next element and a pointer to the stored char
 */
typedef struct _fifo_element {
	struct _fifo_element *next;
	char *word;
} fifo_element;

/**
 * @brief stores the front of the FIFO
 */
typedef struct	{
	fifo_element *front;
} fifo;

/**
 * @brief initializes the FIFO data structure
 */
fifo* fifo_init();

/**
 * @brief initializes a FIFO node
 */
fifo_element *new_element(char word);

/**
 * @brief checks if the FIFO has elements
 */
int fifo_is_empty(fifo *f1);

/**
 * @brief prints the chars in the FIFO
 */
void fifo_print(fifo *f1);

/**
 * @brief returns the char stored in the front of the FIFO
 */
char fifo_top(fifo *f1);

/**
 * @brief removes the front element of the FIFO
 */
int fifo_pop(fifo *f1);

/**
 * @brief puts a new element into a FIFO
 *
 * @param word char to put into the new element
 */
int fifo_push(fifo *f1, char word);

/**
 * @brief deletes the FIFO data structure
 */
int fifo_delete(fifo *f1);

#endif
