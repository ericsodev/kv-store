#include "queue.h"
#include <assert.h>
#include <string.h>

int testQueueBasic() {
	Queue* q = createQueue();
	enqueue(q, "foobar");
	enqueue(q, "foobar2");
	enqueue(q, "hello world");
	assert(q->size == 3);

	char* a;

	a=dequeue(q);
	assert(q->size==2);
	assert(strcmp(a, "foobar")==0);

	a=dequeue(q);
	assert(strcmp(a, "foobar2")==0);

	enqueue(q, "foobar3");
	enqueue(q, "foobar4");

	a=dequeue(q);
	assert(strcmp(a, "hello world")==0);

	assert(q->size == 2);
	freeQueue(q);
	return 0;
}
int main() {
	testQueueBasic();
	return 0;
}
