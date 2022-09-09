//Name: Mehmet Fatih Celik
//ID: 2385268

#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int val;
	struct Node *next;
};

struct Node *InsertProduct(struct Node *product);
struct Node *PriceChanges(struct Node *product);
void PrintPriceChanges(struct Node *priceDiff);

int main(){
	int choice;
	struct Node *product;
	struct Node *priceDiff;
	
	do{
		printf("****************************************************\n");
		printf("1) Create yearly price for the product\n");
		printf("2) Display yearly price changes for the product\n");
		printf("3) Exit\n");
		printf("What would you like to do? ");
		scanf("%d",&choice);
		printf("****************************************************\n");
		if(choice==1)
			product =InsertProduct(product);
		else if(choice==2){
			priceDiff = PriceChanges(product);
			PrintPriceChanges(priceDiff);
		}
		else if(choice!=3)
			printf("Please enter a valid number!\n");
		
	}while(choice!=3);
	
	return 0;
}

struct Node *InsertProduct(struct Node *product){
	product = (struct Node *)malloc(sizeof(struct Node));
	product->next=NULL;
	struct Node *tmp, *tail;
	tail = product;
	
	int num_years, i, price;
	printf("How many years? ");
	scanf("%d",&num_years);
	
	printf("Enter prices for the product: ");
	for(i=0;i<num_years;i++){
		scanf("%d",&price);
		
		tmp = (struct Node *)malloc(sizeof(struct Node));
		tmp->next=NULL;
		tmp->val=price;
		tail->next=tmp;
		tail=tmp;
	}
	printf("Prices for the product is created successfully!\n");
	
	return product;
}

struct Node *PriceChanges(struct Node *product){
	struct Node *tmp=product->next;
	struct Node *priceDiff, *temp, *tail;
	
	priceDiff = (struct Node *)malloc(sizeof(struct Node));
	priceDiff->next=NULL;
	tail=priceDiff;
	
	while(tmp->next){
		temp = (struct Node *)malloc(sizeof(struct Node));
		temp->next=NULL;
		temp->val= tmp->next->val-tmp->val;
		tail->next=temp;
		tail=temp;
		
		tmp=tmp->next;
	}
	
	return priceDiff;
}

void PrintPriceChanges(struct Node *priceDiff){
	printf("Changes per year are as follows:\n");
	int i=1;
	struct Node *temp=priceDiff->next;
	
	while(temp){
		if (temp->val>0)
			printf("Year %d: Price increased %d tl\n",i,temp->val);
		else if (temp->val<0)
			printf("Year %d: Price decreased %d tl\n",i,abs(temp->val));
		else
			printf("Year %d: Price didnt change!\n",i);
		
		temp=temp->next;
		i++;
	}
}
