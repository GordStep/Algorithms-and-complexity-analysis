#define QUEUE_MAX_LENGTH 100

typedef struct Queue {
	void* p[QUEUE_MAX_LENGTH];
	unsigned int head;
	unsigned int tail;
} Queue;

int queueEmpty(Queue* q);

void queuePush(Queue* q, void* p);

void* queuePop(Queue* q);

void queueInit(Queue* q);

int size(Queue* q);
