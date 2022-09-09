#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue CreateQueue(void){
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
	return q;
}

void Enqueue(Queue q){
	struct Node *t;
	t = (struct Node*)malloc(sizeof(struct Node));
	t->next = NULL;
	t->startingTime = rand()%121;
	t->bringingTime = 10 + rand()%111;
	q->rear->next = t;
	q->rear = t;
	q->size++;
}

void sortStartingTime(Queue q){
	int swapped, temp;
	struct Node *t = NULL;
	struct Node *t2;
	
	do{
		swapped = 0;
        t2 = q->front->next;
        
        while (t2->next != t){
        	if (t2->startingTime > t2->next->startingTime){
        		temp = t2->startingTime; // swapping startingTime
        		t2->startingTime = t2->next->startingTime;
        		t2->next->startingTime = temp;
        		
        		temp = t2->bringingTime; // swapping bringingTime
        		t2->bringingTime = t2->next->bringingTime;
        		t2->next->bringingTime = temp;
        		
        		swapped = 1;
			}
			t2 = t2->next;
		}
		t = t2;
		
	}while(swapped);
}

void Dequeue(Queue q){
	struct Node *removal;
	removal = q->front->next;
	q->front->next = removal->next;
	free(removal);
	q->size--;
	if (q->size == 0)
		q->rear = q->front;
}
