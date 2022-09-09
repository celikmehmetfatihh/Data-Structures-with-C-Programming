//Name:Mehmet Fatih Çelik
//ID: 2385268

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(){
	srand(time(NULL));
	int orders, i;
	Queue q;
	q = CreateQueue();
	
	printf("------- Simple book shop system-----\n");
	printf("How many orders? ");
	scanf("%d",&orders);
	
	for(i=0; i<orders; i++)// Enqueue all the orders randomly, we didnt initialize userID here
		Enqueue(q);
	sortStartingTime(q); // we sorted our list based on the startingTime
	
	
	int ID = 1;
	struct Node *traversal = q->front->next;
	while(traversal){ // we initialized the userIDs in this while loop
		traversal->userID = ID;
		ID++;
		
		traversal = traversal->next;
	}
	
	float totalWaiting = 0;
	int waitingTime = 0;
	int endTime;
	int startTime;
	for(i=0; i<orders; i++){
		if (i != 0){
			if(q->front->next->startingTime > endTime)
				startTime = q->front->next->startingTime;
			else
				startTime = endTime;
			
			endTime = startTime + q->front->next->bringingTime;
				
			waitingTime = endTime - q->front->next->startingTime;
			if (waitingTime < 0)
				waitingTime = 0;
			totalWaiting += waitingTime;

					
			printf("Order ID %d\n",q->front->next->userID);
			printf("StartTime : %d\n",startTime);
			printf("EndTime: %d\n",endTime);
			printf("Waiting time: %d\n",waitingTime);
			Dequeue(q);
		}
		else{// if i == 0
		printf("Order ID %d\n",q->front->next->userID);
		printf("StartTime : %d\n",q->front->next->startingTime);
		
		endTime = q->front->next->bringingTime + q->front->next->startingTime;
		printf("EndTime: %d\n",endTime);
		printf("Waiting time: %d\n",waitingTime);
		Dequeue(q);
		}
	}
	
	printf("The average waiting time of the system %.2f",totalWaiting/orders);
	
	return 0;
}
