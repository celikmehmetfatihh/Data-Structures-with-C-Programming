struct Node{
	int userID;
	int startingTime;
	int bringingTime;
	struct Node *next;
};

struct QueueRecord{
	struct Node *front;
	struct Node *rear;
	int size;
};
typedef struct QueueRecord *Queue;

Queue CreateQueue(void);
void Enqueue(Queue);
void sortStartingTime(Queue);
void Dequeue(Queue);
