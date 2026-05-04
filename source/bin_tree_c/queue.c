#include <stdlib.h>

#include "queue.h"

int queueEmpty(Queue* q)
{
	return (q->head == q->tail);
}

int size(Queue* q)
{
	if (q->head > q->tail)
    	return QUEUE_MAX_LENGTH - q->head + q->tail;
  	else
    	return q->tail - q->head;
}

void queuePush(Queue* q, void* ptr) 
{
	if (size(q) != QUEUE_MAX_LENGTH)
	{
		q->p[q->tail] = ptr;
		q->tail = (q->tail + 1) % QUEUE_MAX_LENGTH;
	}
};

void queueInit(Queue* q)
{
	q->head = 0;
	q->tail = 0;
}

void* queuePop(Queue* q) 
{
	if (queueEmpty(q))
		return NULL;
	void* x = q->p[q->head];
	q->head = (q->head + 1) % QUEUE_MAX_LENGTH;

	return x;
};

