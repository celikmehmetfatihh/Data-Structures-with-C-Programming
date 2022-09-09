struct Node{
	char deliveryType;
	int purchaseTime;
	int deliveryTime;
	int deliveryStartTime;
	int courierID;
	char amountOfPurchase;
	struct Node *next;
};

struct QueueRecord{
	struct Node *front;
	struct Node *rear;
	int size;
};

struct ListRecord{
	struct Node *head;
	struct Node *tail;
	int size;
};

typedef struct QueueRecord *Queue;
typedef struct ListRecord *List;

int isEmptyQueue(Queue);
void parseInput(int, char *[], int *, int *, int *, int *);
List createCustomerList(int, int, int, int);
Queue initialiseSimulator(int [], int);
void newCustomer(Queue, struct Node *);
struct Node* serveCustomer(Queue);
void reportStatistics(int, int, int, int, int, int [], int, int, int, int, int);
