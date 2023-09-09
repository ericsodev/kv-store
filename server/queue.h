// front of queue is head of LL
typedef struct Entry {
	struct Entry* prev;
	struct Entry* next;
	char* value;
} Entry;

typedef struct {
	Entry* head;
	Entry* tail;
	unsigned int size;
} Queue;



// does not copy value
Queue* createQueue(void);

// does not copy value
void enqueue(Queue* queue, char* value);

// does not delete internal value pointer
char* dequeue(Queue* queue);

void freeQueue(Queue* queue);
