#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
	char station;
	struct NODE* next;
} node;

node* createNode(char c){
	node* temp = (node*)malloc(sizeof(node));
	temp->station = c;
	temp->next = NULL;
	return temp;
}

node* addNode(node* head, char c){
	node* temp = head;
	if(head == NULL){
		return createNode(c);
	}
	while(head->next != NULL){
		head = head->next;
	}
	head->next = createNode(c);
	return temp;
}

void printList(node* head){
	while(head != NULL){
		printf("%c ", head->station);
		head = head->next;
	}
	printf("\n");
}

typedef struct Train
{
	int seats;
	int basePrice;
	int trainNo;
	node* route;
} train;

train *createTrain(int tn, int prs, int seats,char routes[], int routeSize)
{
	train *temp = (train *)malloc(sizeof(train));
	temp->trainNo = tn;
	temp->basePrice = prs;
	temp->seats = seats;
	temp->route = NULL;
	for (int i = 0; i < routeSize; i++)
	{
		temp->route = addNode(temp->route, routes[i]);
	}	
	return temp;
}

void bookTickets(train *tra, int n)
{
	(tra->seats) -= n;
	printf("Total fare = %d\n", n * tra->basePrice);
	printf("Ticket BOOKED\n");
}

void printTrainDetails(train* gadi){
	if(gadi == NULL){
		return;
	}
	printf("%d\t%d\t%d\n",gadi->trainNo, gadi->seats, gadi->basePrice);
	
}

void getTrain(char src, char dest, train* gadi[], int n){
	int trainAvail[n];
	for (int i = 0; i < n; i++)
	{
		trainAvail[i] = 0;
	}
	
	for (int i = 0; i < n; i++)
	{
		node* temp = gadi[i]->route;
		while(temp != NULL){
			if(temp->station == src){
				while(temp != NULL){
					if(temp->station == dest){
						trainAvail[i] = 1;
						break;
					}
					temp = temp->next;
				}
				break;
			}
			temp = temp->next;
		}
	}
	printf("Available Trains\n");
	printf("TrainNo.\tFare\t\tSeats\n");
	printf("------------------------------------\n");
	for (int i = 0; i < n; i++)
	{
		if(trainAvail[i]){
			printf("%-15d\t%-15d\t%-15d\n",gadi[i]->trainNo, gadi[i]->basePrice,gadi[i]->seats);
		}
	}	
}

int getTrainByN(train* gadi[], int n, int trainNo){
	for (int i = 0; i < n; i++)
	{
		if(gadi[i]->trainNo == trainNo){
			return i;
		}
	}
	return -1;
}

int main()
{
	FILE *inp = fopen("./reservation/trainData.txt", "r");
	if (inp == NULL)
	{
		printf("File does not exist\n");
		return 1;
	}
	char temp[12];
	int n;
	fscanf(inp,"%d",&n);
	train* gadi[n];
	for (int i = 0; i < n; i++)
	{
		int tn, prs, seat;
		fscanf(inp, "%d %d %d",&tn,&seat,&prs);
		int routeSize;
		fscanf(inp, "%d", &routeSize);
		char routes[routeSize];
		for (int i = 0; i < routeSize; i++)
		{
			routes[i] = getc(inp);
		}
		gadi[i] = createTrain(tn,prs,seat,routes,routeSize);
	}
	fclose(inp);
	int t=1,ch;
	while(t){
		printf("Choose:\n1)Find trains\n2)Book Ticket\n3)Exit\n: ");
		scanf("%d", &ch);
		char src,dest;
		int tnu;
		int trainIndex;
		switch (ch)
		{
		case 1:
			printf("Enter src : ");
			scanf(" %c", &src);
			printf("Enter dest : ");
			scanf(" %c", &dest);
			getTrain(src,dest,gadi,n);
			break;
		case 2:
			printf("Enter train no. : ");
			scanf("%d",&ch);
			trainIndex = getTrainByN(gadi,n,ch);
			if(trainIndex == -1)
			{
				printf("Invalid train no.\n");
				break;
			}
			printf("Enter number of tickets : ");
			scanf("%d", &tnu);
			if(gadi[trainIndex]->seats < tnu){
				printf("Not enough seats\n");
				break;
			}
			bookTickets(gadi[trainIndex],tnu);
			break;
		case 3:
			t=0;
			break;
		default:
			printf("Invalid Option\n");
			break;
		}
	}		

	return 0;
}
