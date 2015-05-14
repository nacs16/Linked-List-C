/*
Filename: A4.c
Part of: Assignment 4
Created by: Nick Solano nsolano
Created on: 2-9-14
Last Modified by: Nick Solano nsolano
Last Modified on: 2-9-14
*/

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

struct cricket_player{
	char team_name[20];
	char player_name[20];
	float avg;	
};

struct NODE{
	int n;
	struct NODE *next;
};

//GLOBAL VARIABLES FOR CRICKET
struct cricket_player teams[5][11]; //contains all cricket players and team info
int num_teams; //number of teams user enters

//GLOBAL VARIABLES FOR LLIST
struct NODE *head;
struct NODE *temp;

//FUNCTION PROTOTYPES:
void pick();
//CRICKET FUNCTIONS
int mystrcmp(char x[], char y[]);
void allocateTeams();
void fillTeams();
void printTeams();
void cricket();
//LLIST FUNCTIONS
void llistFunction();
void insert(int x, int p, int f);
void delete(int p, int f);
void modify(int x, int p);
void printllist();
struct NODE *search_value(int p);

void main(){
	pick();
}

void pick(){
	int x;
	printf("Enter '1' for Cricket, '2' for llist: ");
	scanf("%d", &x);
	if(x == 1){
		printf("\nCRICKET START\n");
		cricket();
	}
	if(x == 2){
		printf("\nLINKED LIST START\n");
		head = (struct NODE *)malloc(sizeof(struct NODE));
		temp = (struct NODE *)malloc(sizeof(struct NODE));
		head->next = NULL;
		int y;
		printf("Insert value of first node: ");
		scanf("%d", &y);
		head->n = y;
		llistFunction();
	}
	if(x != 1 && x != 2){
		printf("Try Again\n");
		pick();
	}
}

// compares two string. returns 1 if they are the same, 0 if different. 
int mystrcmp(char x[], char y[]){
	int xl, yl, i;
	xl = strlen(x);
	yl = strlen(y);
	if (xl != yl){return 0;}
	else{
		for(i = 0; i < xl; i++){
			if (x[i] != y[i]){return 0;}
		}
	}
	return 1;
}

// allocateTeams() fills teams array with cricket_player structs
void allocateTeams(){
	struct cricket_player blank;
	blank.avg = -1.0; //useful later to not overwrite existing players, or print blank ones.
	int i, j;
	for(i = 0; i < 5; i++){
		for(j = 0; j < 11; j++){
			teams[i][j] = blank;
		}
	}
}

// fillTeams() fills teams[][] with user input data.
void fillTeams(){
	int i, j, k; // loop counters
	int t, players; //team 0-4, player 0-10
	char t_name[5][20]; //keep track of all team names for reference when putting players into correct spot in teams[][]
	float AVG;
	char NAME[20];
	char TEAM[20];
	
	//TEAM NAMES
	printf("Enter the number of teams you wish to record: ");
	scanf("%d", &num_teams);
	for(i = 0; i < num_teams; i++){ //i represents team, j is player
		printf("Enter the name(s) of the teams: ");
		scanf("%s", &t_name[i]); //save current team name
		for(j = 0; j < 11; j++){ //fill team j with supplied team name.
			strcpy(teams[i][j].team_name, t_name[i]);
		}
	}
	
	//PLAYER DATA
	printf("\nEnter the TOTAL number of players for all teams: ");
	scanf("%d", &players);
	int DONE;
	for(i = 1; i <= players; i++){
		printf("Enter the %d Player name, Team name, and batting average: ", i);
		scanf("%s %s %f", &NAME, &TEAM, &AVG);
		DONE = 0;
		for (j = 0; j < 5; j++){
			if (mystrcmp(TEAM, teams[j][0].team_name) != 0){ //find which team slot in teams[j] to put input data.
				for (k = 0; k < 11; k++){ //find empty player slot teams[j][k]
					if (teams[j][k].avg == -1.0){
						teams[j][k].avg = AVG;
						strcpy(teams[j][k].player_name, NAME);
						DONE = 1;
						break;
					}
				}
			}
			if(DONE) break;
		}
	}
}

void printTeams(){
	printf("\n\nListing of players and batting average according to team names:\n");
	
	int i, j; //loop counters
	for (i = 0; i < num_teams; i++){
		printf("\n%s-\n", teams[i]);
		for (j = 0; j < 11; j++){
			if (teams[i][j].avg < 0.0){
				break;
			} else {
				printf("        %s   %f\n", teams[i][j].player_name, teams[i][j].avg);
			}
		}
	}
}

void cricket(){
	allocateTeams();
	fillTeams();
	printTeams();
}

void llistFunction(){
	int input, x, p;
	while (input != 8){
		printf("\nPlease enter your choice\n");
		printf("1. INSERT a node at the END of linklist\n");
		printf("2. INSERT a node at the BEGINNING of linklist\n");
		printf("3. DELETE a node at the END of linklist\n");
		printf("4. DELETE a node from the BEGINNING of linklist\n");
		printf("5. INSERT a node in the MIDDLE of linklist\n");
		printf("6. MODIFY a node from the MIDDLE of linklist\n");
		printf("7. MODIFY any node in linklist\n");
		printf("8. EXIT\n");
		scanf("%d", &input);
	
		switch (input){
			case 1:
				printf("Enter your node in the list\n");
				scanf("%d", &x);
				insert(x, 0, 2);
				printf("The link list currently has these nodes:\n");
				printllist();
				break;
			case 2:
				printf("Enter the value for the node you want to insert at the beginning\n");
				scanf("%d", &x);
				insert(x, 0, 0);
				printf("The link list currently has these nodes:\n");
				printllist();
				break;
			case 3:
				delete(0, -1);
				printf("Deleted node at the end of linked list\n");
				printf("The link list currently has these nodes:\n");
				printllist();
				break;
			case 4:
				delete(0, 0);
				printf("Deleted node at the beginning of linked list\n");
				printf("The link list currently has these nodes:\n");
				printllist();
				break;
			case 5:
				printf("Enter the value of the node after which you want to insert a new node\n");
				scanf("%d", &p);
				if (search_value(p) == NULL){
					break;
				}
				printf("Enter the value of the new node\n");
				scanf("%d", &x);
				insert(x, p, 1);
				printf("The link list currently has these nodes:\n");
				printllist();
				break;
			case 6:
				printf("Enter the value of the node that precedes the node you want to delete\n");
				scanf("%d", &p);
				if (search_value(p) == NULL){
					break;
				}
				delete(p, 1);
				printf("The link list currently has these nodes:\n");
				printllist();
				break;
			case 7:
				printf("Enter the value of the node you want to modify\n");
				scanf("%d", &p);
				if (search_value(p) == NULL){
					break;
				}
				printf("Enter the new value for this node:\n");
				scanf("%d", &x);
				modify(x, p);
				printf("The link list currently has these nodes:\n");
				printllist();
				break;
			case 8:
				printf("EXIT\n");
				input = 8;
				break;
			default:
				printf("That is not a valid menu option\n");
				break;
		}
	}
}

void insert(int x, int p, int f){ //insert node x into position p, function f (beginning = 0, end = 2, any 1)
	struct NODE *new;
	new = (struct NODE *)malloc(sizeof(struct NODE));
	new->next = NULL;
	if (f == 0){ //insert beginning
		temp = head;
		new->next = temp;
		new->n = x;
		head = new;
		return;
	}
	if (f == 2){ //insert end
		temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = new;
		new->n = x;
		new->next = NULL;
		return;
	}
	if (f == 1){// insert middle
		temp = search_value(p);
		new->next = temp->next;
		temp->next = new;
		new->n = x;
	}
}

void delete(int p, int f){ // position p, function f (beginning = 0, end = -1, middle = 1)
	if (f == 0){ //delete from beginning
		head = head->next;
		return;
	}
	if (f == -1){ //delete from end
		temp = head;
		if (temp->next == NULL){
			head->next = NULL;
		}
		while(temp->next->next != NULL){
			temp = temp->next;
		}
		temp->next = NULL;
		return;
	}
	if (f == 1){ //delete from middle
		if (head->next->n == p){
			head->next = head->next->next;
		}
		temp = head;
		struct NODE *del = search_value(p);
		while (temp->next->n != del->n){
			temp = temp->next;
		}
		temp->next = temp->next->next;
		return;
	}
}

void modify(int x, int p){ // new val x, old val p
	if (head->n == p){
		head->n = x;
		return;
	}
	temp = head;
	while(temp->next->n != p){
		temp = temp->next;
	}	
	temp->next->n = x;
}

void printllist(){
	temp = head;
	while (temp != NULL){
		printf("%d->", temp->n);
		temp = temp->next;
	}
	printf("\n");
}

struct NODE *search_value(int p){
	if (head->n == p){return head;}
	temp = head;
	while(temp->next != NULL){
		if (temp->next->n == p){
			return temp->next; // Found
		} else {
			temp = temp->next;
		}
	}
	printf("NOT FOUND\n");
	return NULL; // Not found
}