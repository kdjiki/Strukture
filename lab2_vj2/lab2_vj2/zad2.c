/*
2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define WRONG_CHAR (1)
#define MALLOC_ERROR (-1)


typedef struct _Person* Position;
typedef struct _Person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
} Person;

Position initialization(Position);
int addToTheBeginnig(Position);
int menu();
int printList(Position);
int addToTheEnd(Position);

int main()
{
	Position head = NULL;
	head = initialization(head);
	char letter = "\n";
	int i=1;
	while (i==1)
	{
		menu();
		scanf(" %c", &letter);
		switch (toupper(letter))
		{
		case 'A':
			addToTheBeginnig(head);
			break;
		case 'P':
			printList(head);
			break;
		case 'E':
			addToTheEnd(head);
			break;
		case 'X':
			i = 0;
			free(head);
			return EXIT_SUCCESS;
			break;
		default:
			free(head);
			printf("Wrong character!\n");
			return WRONG_CHAR;
			break;
		}
	}

	return EXIT_SUCCESS;
}

Position initialization(Position p) 
{
	p = (Position)malloc(sizeof(Person));
	if (p == NULL)
	{
		printf("Error\n");
		return MALLOC_ERROR;
	}
	strcpy(p->name, "");
	strcpy(p->surname, "");
	p->birthYear = 0;
	p->next = NULL;
	return p;
}
int menu()
{
	printf("Enter 'A' to add a member to the beginning:\nEnter 'E' to add a member to the end of list:\nEnter 'P' to print the list\nEnter 'X' for exit\n");

	return 0;
}

int addToTheBeginnig(Position p)
{
	Position new=NULL;
	new = initialization(new);

	if (p == NULL)
	{
		printf("Error\n");
		return MALLOC_ERROR;
	}

	printf("NAME:\n");
	scanf("%s", &new->name);
	printf("SURNAME:\n");
	scanf("%s", &new->surname);
	printf("YEAR:\n");
	scanf("%d", &new->birthYear);

	new->next = p->next;
	p->next = new;

	return EXIT_SUCCESS;
}

int printList(Position p)
{
	printf("___________________________________\n");
	printf("NAME	SURNAME		BIRTH YEAR\n");
	p = p->next;
	while(p != NULL)
	{
		printf("%s	", p->name);
		printf("%s	", p->surname);
		printf("	%d\n", p->birthYear);
		p = p->next;
	}
	printf("\n\n");

	return EXIT_SUCCESS;
}
int addToTheEnd(Position p)
{
	Position new = NULL;
	while (p->next!=NULL)
	{
		p = p->next;
	}
	new=initialization(new);

	if (p == NULL)
	{
		printf("Error\n");
		return MALLOC_ERROR;
	}

	printf("NAME:\n");
	scanf("%s", &new->name);
	printf("SURNAME:\n");
	scanf("%s", &new->surname);
	printf("YEAR:\n");
	scanf("%d", &new->birthYear);

	new->next = NULL;
	p->next = new;

	return EXIT_SUCCESS;
}