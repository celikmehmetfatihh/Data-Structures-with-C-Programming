//Name: Mehmet Fatih Çelik
//ID: 2385268

#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int  year;
	int prices;
	struct Node *next;
};

struct ListRecord
{
	struct Node *head;
	struct Node *tail;
	int size;
};

void PrintProducts(struct ListRecord *);
int findCheapest(struct ListRecord *);

int main(){
	
	int choice, years,i, cheapest;
	struct ListRecord *product;
	
	do{
		printf("****************************************************\n");
		printf("1) Create yearly price for the product\n");
		printf("2) Display yearly price for the product\n");
		printf("3) Display the cheapest product info\n");
		printf("4) Exit\n");
		printf("What would you like to do? ");
		scanf("%d",&choice);
		printf("****************************************************\n");
		
		if(choice == 1){
			printf("How many years? ");
			scanf("%d",&years);
			product = (struct ListRecord*)malloc(sizeof(struct ListRecord));
			if (product == NULL){
				printf("Out of the memory!\n");
				exit(1);
			}
			
			product->head = (struct Node*)malloc(sizeof(struct Node));
			if (product->head == NULL){
				printf("Out of memory!\n");
				exit(1);
			}
			
			product->head->next=NULL;
			product->tail= product->head;
			product->size=0;
			
			for(i=0;i<years;i++){			
				struct Node *temp;
				temp = (struct Node*)malloc(sizeof(struct Node));
				printf("Enter price and year for the product: ");
				scanf("%d %d",&temp->prices,&temp->year);
				
				product->tail->next=temp;
				temp->next=NULL;
				product->tail=temp;
				product->size++;
			}
			printf("Prices and year info for the product is created successfully!\n");
		}
		
		else if (choice==2)
			PrintProducts(product);
		
		else if (choice==3){
			int year;
			cheapest = findCheapest(product);
			
			struct Node *temp=product->head->next;
			
			while(temp){
				if (cheapest == temp->prices)
					year = temp->year;
				
				temp = temp->next;
			}
			printf("The cheapest price of the product is %d tl in %d!\n",cheapest,year);
		}	
	}while(choice!=4);
	
	return 0;
}

void PrintProducts(struct ListRecord *product){
	struct Node *temp;
	temp = product->head->next;
	
	printf("Yearly price for the product\n");

	while(temp){
		printf("%d: %d tl\n",temp->year,temp->prices);
		
		temp=temp->next;
	}
}

int findCheapest(struct ListRecord *product){
	int cheapest=product->head->next->prices;
	struct Node *temp;
	temp= product->head->next->next;
	
	while(temp){
		if (temp->prices < cheapest)
			cheapest = temp->prices;
		
		temp= temp->next;
	}
	
	return cheapest;
}
