/*
	Mehmet Fatih Çelik 2385268

	Hocam for some reason that I dont know from where but in the main, Sometimes I compile it gives run-time error, and sometimes
	it does not give error, compiles but last function(displaying) is not fully correct, so I want from you to please
	note that.
	
	I actually have a problem in the main, the other functions are works perfectly fine. You can try hocam.
	But I couldnt have time to fix the error which is in the main. I hope you evaluate the assignment one by one
	the functions, thanks.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "queue.h"


int main(int argc, char *argv[]){
	srand(time(NULL));
	int noOfCustomers, noOfCouriers, maxPurchaseTime, maxDeliveryTime;
	
	parseInput(argc, argv, &noOfCustomers, &noOfCouriers, &maxPurchaseTime, &maxDeliveryTime);
	
	List L;
	L = createCustomerList(noOfCustomers, noOfCouriers, maxPurchaseTime, maxDeliveryTime);
	
	Queue q;
	int couriers[noOfCouriers];
	q = initialiseSimulator(couriers, noOfCouriers);
	//printing couriers
	int i,j;
	for(i=0;i<noOfCouriers;i++)
		printf("%d. courier = %d\n",i+1,couriers[i]);
	
	int clock=0, available = 0, countAvailable, temp;
	int purchaseTime, deliveryTime, waitingTime, deliveryStartTime, courierID;
	char deliveryType, amountOfPurchase;
	int servedCustomer=0, numE = 0, numS = 0, numF = 0, counterCourier[noOfCouriers] ,totalWaitingTime = 0, numA = 0, numB = 0, maxWaitingTime = 0;
	struct Node *traversal = L->head->next;
	
	for(i=0;i<noOfCustomers;i++){
		
		countAvailable = 0;
		// for checking if any of the couriers is available or not
		for(j=0;j<noOfCouriers;j++){
			if(couriers[i] == 1){
				available = 1;
				countAvailable++;
			}
		}
		// if there is no customer in the queue, and at least one of the couriers is available
		if(traversal->purchaseTime == clock && available){
			temp = rand()%countAvailable;
			
			int temp_counter = 0;
			for(j=0; j<noOfCouriers;j++){
				if(couriers[j] && temp_counter == temp){// if courier = 1 and counter = randomValue
					couriers[j] = 0;
					traversal->courierID = j+1;
					break;
				}
				else if(couriers[j] && temp_counter != temp)
					temp_counter++; //if courier = 1 and counter != randomValue
			}
			
			//printing couriers
			for(j=0;j<noOfCouriers;j++)
				printf("%d. courier = %d\n",j+1,couriers[j]);
			
			purchaseTime = traversal->purchaseTime;
			deliveryTime = traversal->deliveryTime;
			traversal->deliveryStartTime = clock;
			waitingTime = traversal->deliveryStartTime - purchaseTime;
			
			if(waitingTime > maxWaitingTime)
				maxWaitingTime = waitingTime;
			
			L->head->next = traversal->next;//putting the first node to the last
			L->tail->next = traversal;
			traversal = L->tail;
			traversal->next = NULL;
		}
		
		// Couriers are not available, we are putting customer into the queue
		else if(traversal->purchaseTime == clock && !available){
			newCustomer(q, traversal);
			
			L->head->next = traversal->next;//putting the first node to the last
			L->tail->next = traversal;
			traversal = L->tail;
			traversal->next = NULL;
		}
		
		else if(purchaseTime+deliveryTime < clock && !isEmptyQueue(q) && available){
			struct Node *customer;
			couriers[traversal->courierID-1] = 1;
			customer = serveCustomer(q);
			
			purchaseTime = customer->purchaseTime;
			deliveryTime = customer->deliveryTime;
			deliveryStartTime = customer->deliveryStartTime;
			customer->deliveryStartTime = clock;
			deliveryType = customer->deliveryType;
			amountOfPurchase = customer->amountOfPurchase;
			courierID = customer->courierID;
			waitingTime = customer->deliveryStartTime - purchaseTime;
			
			
			if(waitingTime > maxWaitingTime)
				maxWaitingTime = waitingTime;
		}
		
		//when robot finishes at deliveryTime + deliveryStartTime
		else if(deliveryStartTime+ deliveryTime == clock && !available){
			couriers[traversal->courierID-1] = 1;
			servedCustomer++;
			
			if(deliveryType == 'E')
				numE++;
			if(deliveryType == 'S')
				numS++;
			if(deliveryType == 'F')
				numF++;
			
			counterCourier[courierID-1]++;
			totalWaitingTime += waitingTime;
			
			if(amountOfPurchase == 'A')
				numA++;
			if(amountOfPurchase == 'B')
				numB++;
					
			clock--;
		}
		clock++;
	}
	
	reportStatistics(noOfCouriers, noOfCustomers, numE, numS, numF, counterCourier, clock, totalWaitingTime, maxWaitingTime, numA, numB);
	
	return 0;
}
