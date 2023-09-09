#include "queue.h"
#include <stdlib.h>


// does not copy value
Queue* createQueue() {
	Queue* e = malloc(sizeof(Queue));
	e->head=0;
	e->tail=0;
	return e;
}

// does not copy value
void enqueue(Queue* queue, char* value) {
	Entry* e = malloc(sizeof(Entry));
	e->value = value;
	e->next=0;
	if (queue->head==0) {
		queue->head=e;
		queue->tail=e;
		e->prev=0;
	} else {
		queue->tail->next=e;
		e->prev=queue->tail;
		queue->tail=e;
	}
	queue->size++;
}

// does not delete internal value pointer
char* dequeue(Queue* queue) {
	if (queue->size == 0) {
		return 0;
	}

	Entry* e = queue->head;

	if (queue->size==1) {
		queue->head=0;
		queue->tail=0;
	} else {
		queue->head=e->next;
		queue->head->prev=0;
	}
	queue->size--;
	char* val = e->value;
	free(e);
	return val;
}

void freeQueue(Queue* q) {
	Entry* curr = q->head;
	Entry* next = 0;
	while (curr != 0) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(q);
}
