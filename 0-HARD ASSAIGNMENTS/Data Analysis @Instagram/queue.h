struct QueueNode{
	AVLTree val;
	struct QueueNode *next;
};

struct QueueRecord{
	struct QueueNode *front;
	struct QueueNode *rear;
	int size;
};
typedef struct QueueRecord *Queue;

Queue createQueue();
void Enqueue(Queue, AVLTree);
AVLTree Dequeue(Queue);
