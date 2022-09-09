#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void parseInput(int argc, char *argv[], int *noOfCustomers, int *noOfCouriers, int *maxPurchaseTime, int *maxDeliveryTime){
	if (argc < 2)
		printf("No argument has been passed through the command line!\n");
	
	*noOfCustomers = atoi(argv[1]);
	*noOfCouriers = atoi(argv[2]);
	*maxPurchaseTime = atoi(argv[3]);
	*maxDeliveryTime = atoi(argv[4]);
}

List createCustomerList(int noOfCustomers, int noOfCouriers, int maxPurchaseTime, int maxDeliveryTime){
	List L;
	L = (struct ListRecord*)malloc(sizeof(struct ListRecord));
	if (L == NULL){
		printf("Out of memory!");
		exit(-1);
	}	
	
	L->size = 0;
	L->head = (struct Node*)malloc(sizeof(struct Node));
	if (L->head == NULL){
		printf("Out of memory!");
		exit(-1);
	}
	
	L->head->next = NULL;
	L->tail = L->head;
	
	int i, temp;
	struct Node *t;
	for(i=0;i<noOfCustomers;i++){
		t = (struct Node*)malloc(sizeof(struct Node));
		t->next = NULL;
		
		temp = 1+rand()%3;
		if (temp == 1)
			t->deliveryType = 'E';
		else if (temp == 2)
			t->deliveryType = 'S';
		else if (temp == 3)
			t->deliveryType = 'F';
		printf("\n %c->",t->deliveryType);
		
		t->purchaseTime = 1 + rand()%maxPurchaseTime;
		printf(" purchase: %d->",t->purchaseTime);
		
		t->deliveryTime = 1 + rand()%maxDeliveryTime;
		printf(" delivery: %d->",t->deliveryTime);
		
		temp = 1 + rand()%1000;
		if (temp>= 500)
			t->amountOfPurchase = 'A';
		else
			t->amountOfPurchase = 'B';
		printf(" amount: %c",t->amountOfPurchase);
			
		
		L->tail->next = t;
		L->tail = t;
		L->size++;
	}
	
	//sorting part
	int swapped;
	t = NULL;
	struct Node *t2;
	
	do{
		swapped = 0;
 		t2 = L->head->next;
 		
 		while (t2->next != t){
 			if (t2->purchaseTime > t2->next->purchaseTime){
 			temp = t2->purchaseTime; // swapping purchaseTime
 			t2->purchaseTime = t2->next->purchaseTime;
 			t2->next->purchaseTime = temp;
 
			temp = t2->deliveryType; // swapping deliveryType
		    t2->deliveryType = t2->next->deliveryType;
			t2->next->deliveryType = temp;
			 
			temp = t2->amountOfPurchase; // swapping amountOfPurchase
			t2->amountOfPurchase = t2->next->amountOfPurchase;
		    t2->next->amountOfPurchase = temp;
			 
			temp = t2->deliveryTime; // swapping deliveryTime
		    t2->deliveryTime = t2->next->deliveryTime;
		    t2->next->deliveryTime = temp;
 
			 swapped = 1;
			}
			t2 = t2->next;
		}	
		t = t2;	
	}while(swapped);
	
	//for printing
	printf("\nAfter swapping:");
	struct Node *traversal = L->head->next;
	while(traversal){
		printf("\n %c->",traversal->deliveryType);
		printf(" purchase: %d->",traversal->purchaseTime);
		printf(" delivery: %d->",traversal->deliveryTime);
		printf(" amount: %c\n",traversal->amountOfPurchase);
		
		traversal = traversal->next;
	}
	return L;
}

Queue initialiseSimulator(int couriers[], int noOfCouriers){
	Queue q;
	q = (struct QueueRecord*)malloc(sizeof(struct QueueRecord));
	if (q == NULL){
		printf("Out of memory!");
		exit(-1);
	}	
	
	q->size = 0;
	q->front = (struct Node*)malloc(sizeof(struct Node));
	if (q->front == NULL){
		printf("Out of memory!");
		exit(-1);
	}
	
	q->front->next = NULL;
	q->rear = q->front;
	
	int i;
	for(i=0;i<noOfCouriers;i++)
		couriers[i] = 1;
	
	return q;	
}

int isEmptyQueue(Queue q){
	if (q->size == 0)
		return 1;
	else
		return 0;
}

void newCustomer(Queue q, struct Node *traversal){
	struct Node *t;
	if(isEmptyQueue){
		q->front->next = traversal;
	}
	else{
		t = q->front;
		
		if (traversal->deliveryType == 'E'){
			if (t->next->deliveryType!= 'E')
				t = t->next;
			else{
				traversal->next = t->next;
				t->next = traversal;
				
				if(traversal->next == NULL)//if last element
					q->rear = traversal;
			}	
		}
		else if(traversal->deliveryType == 'S'){
			if (t->next->deliveryType!= 'E' && t->next->deliveryType!= 'S')
				t = t->next;
			else{
				traversal->next = t->next;
				t->next = traversal;	
			}	
			
			if(traversal->next == NULL)//if last element
				q->rear = traversal;
		}
		else if(traversal->deliveryType == 'F'){
			q->rear->next = traversal;
			q->rear = traversal;
			traversal->next = NULL;
		}
	}	
}

struct Node* serveCustomer(Queue q){
	struct Node *removal;
	removal = q->front->next;
	
	q->front->next = removal->next;
	removal->next = NULL;
	
	return removal;
}

void reportStatistics(int noOfCouriers, int noOfCustomers, int numE, int numS, int numF, int counterCourier[], int clock, int totalWaitingTime, int maxWaitingTime, int numA, int numB){
	int i;
	printf("****************Delivery Statistics*****************\n");
	printf("The number of couriers: %d\n",noOfCouriers);
	printf("The number of customers: %d\n",noOfCustomers);
	printf("Number of customers for each delivery type:\n");
	printf("	Express: %d\n",numE);
	printf("	Standard: %d\n",numS);
	printf("	Free: %d\n",numF);
	printf("Number of customers for each courier:\n");
	for(i=0;i<noOfCouriers;i++)
		printf("	Courier %d:%d\n",i+1,counterCourier[i]);
	
	printf("Completion time: %d\n",clock);
	printf("Average time spent in the queue: %f\n",totalWaitingTime/noOfCustomers);
	printf("Maximum waiting time: %d\n",maxWaitingTime);
	printf("Popular purchase: ");
	
	if(numA > numB)
		printf("A");
	else if(numB > numA)
		printf("B");
	else
		printf("Both are the same!");
}
