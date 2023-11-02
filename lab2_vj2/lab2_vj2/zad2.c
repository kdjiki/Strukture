/*
2. Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
A. dinamički dodaje novi element na početak liste,
B. ispisuje listu,
C. dinamički dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. */

/*
3. Prethodnom zadatku dodati funkcije:
A. dinamički dodaje novi element iza određenog elementa,
B. dinamički dodaje novi element ispred određenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. čita listu iz datoteke.
*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define MALLOC_ERROR (-1)
#define EMPTY_LIST (1)
#define NO_PERSON (2)
#define NO_FILE_ERROR (-2)


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
int findPerson(Position);
int deletePerson(Position);
int addBehindThePerson(Position);
Position findPersonBefore(Position, char*);
int addInFrontOfThePerson(Position);
Position findPersonAfter(Position, char*);
int sort(Position);
int writeInFile(Position);
int readFromFile(Position);
int noRows();
int freeMemory(Position);


int main()
{
	Position head = NULL;
	head = initialization(head);
	char letter = "\n";
	int i=1;
	//Petlja osigurava mogucnost izvodenje vise naredbi dok korisnik ne odluci izaci iz programa
	while (i==1)
	{
		menu();
		scanf(" %c", &letter);
		//Izbornik naredbi koje je moguce izvrsiti 
		switch (toupper(letter))
		{
		case 'A':
			addToTheBeginnig(head);
			break;
		case 'B':
			addBehindThePerson(head);
			break;
		case 'C':
			addInFrontOfThePerson(head);
			break;
		case 'S':
			sort(head);
			break;
		case 'P':
			printList(head->next);
			break;
		case 'E':
			addToTheEnd(head);
			break;
		case 'F':
			findPerson(head->next);
			break;
		case 'W':
			writeInFile(head);
			break;
		case 'R':
			readFromFile(head);
			break;
		case 'D':
			deletePerson(head);
			break;
		case 'M':
			freeMemory(head);
			break;
		case 'X':
			i = 0;
			freeMemory(head);
			free(head);
			return EXIT_SUCCESS;
			break;
		default:
			printf("Wrong character!\n");
			break;
		}
	}

	return EXIT_SUCCESS;
}
//Funkcija za inicijalizaciju strukture i posavljanje njenih varijabli na 0/NULL
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
//Izbornik koji korisniku prikazuje opcije
int menu()
{
	printf("Enter 'A' to add a member to the beginning:\nEnter 'E' to add a member to the end of list:\nEnter 'P' to print the list:\nEnter 'B' to add a member behind the person:\nEnter 'C' to add a member in front of the person:\nEnter 'W' for writing in file:\nEnter 'R' for reading from a file:\nEnter 'S' to sort the list:\nEnter 'F' to search for a person by surname:\nEnter 'D' to delete a person:\nEnter 'M' to delete the entire liste: \nEnter 'X' for exit:\n");

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
int findPerson(Position p)
{
	char surnameF[MAX_SIZE];
	int counter = 0;
	printf("Enter surname of the person you want to find:\n");
	scanf("%s", &surnameF);
	while (p != NULL)
	{
		
		counter++;
		//Usporedba stringova preko funkcije strcmp
		if (strcmp(p->surname, surnameF) == 0)
		{
			printf("___________________________________\n");
			printf("Person is No. %d in the list\n\n", counter);
			printf("NAME	SURNAME		BIRTH YEAR\n");
			printf("%s	", p->name);
			printf("%s	", p->surname);
			printf("	%d\n", p->birthYear);
			return EXIT_SUCCESS;
		}
		p = p->next;
	}
	if(p==NULL)
		printf("Person not found!\n");

	return EXIT_SUCCESS;
}
int deletePerson(Position p)
{
	//Eliminacija pokusaja brisanja prazne liste
	if (p->next == NULL)
	{
		printf("Error! The list is empty!\n");
		return EMPTY_LIST;
	}
	char surnameD[MAX_SIZE];
	Position temp=NULL;
	printf("Enter surname of the person you want to delete:\n");
	scanf("%s", &surnameD);
	while (p->next != NULL)
	{
		if (strcmp(p->next->surname, surnameD) == 0)
		{
			temp = p->next->next;
			free(p->next);
			p->next = temp;
			return EXIT_SUCCESS;
		}
		p = p->next;
	}

	return EXIT_SUCCESS;
}
int addBehindThePerson(Position p)
{
	Position personBefore = NULL;
	Position newPerson=NULL;
	char surname[MAX_SIZE];
	printf("Enter surname of the person after whom you want to add a new member:\n");
	scanf("%s", &surname);
	personBefore = findPersonBefore(p,surname);
	if (personBefore == NULL)
	{
		printf("Wrong surname!\n");
		return NO_PERSON;
	}
	newPerson=initialization(newPerson);
	printf("NAME:\n");
	scanf("%s", &newPerson->name);
	printf("SURNAME:\n");
	scanf("%s", &newPerson->surname);
	printf("YEAR:\n");
	scanf("%d", &newPerson->birthYear);

	newPerson->next = personBefore->next;
	personBefore->next = newPerson;
	

	return EXIT_SUCCESS;
}
Position findPersonBefore(Position p, char* surname)
{
	while (p->next != NULL)
	{
		if (strcmp(p->next->surname, surname) == 0)
		{
			return p->next;
		}
		p = p->next;
	}
	return p->next;
}
int addInFrontOfThePerson(Position p)
{
	Position personBefore = NULL;
	Position newPerson = NULL;
	char surname[MAX_SIZE];
	printf("Enter surname of the person before whom you want to add a new member:\n");
	scanf("%s", &surname);
	personBefore = findPersonAfter(p,surname);
	if (personBefore == NULL)
	{
		printf("Wrong surname!\n");
		return NO_PERSON;
	}
	newPerson = initialization(newPerson);
	printf("NAME:\n");
	scanf("%s", &newPerson->name);
	printf("SURNAME:\n");
	scanf("%s", &newPerson->surname);
	printf("YEAR:\n");
	scanf("%d", &newPerson->birthYear);

	newPerson->next = personBefore->next;
	personBefore->next = newPerson;
	return EXIT_SUCCESS;
}
Position findPersonAfter(Position p, char* surname)
{
	while (p->next != NULL)
	{
		if (strcmp(p->next->surname, surname) == 0)
		{
			return p;
		}
		p = p->next;
	}
	return p;
}
int sort(Position p)
{
	Position j=NULL, prev_j=NULL, temp=NULL, end=NULL;
	end = NULL;
	//Bubble sort
	while (p->next != end)
	{
		prev_j = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->surname, j->next->surname) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		//Kada najveca vrijenost stigne na kraj zbog postavljanja end-a petlja vise ne provjerava tu vrijednost i ubrzava se rad funkcije
		end = j;
	}

	return EXIT_SUCCESS;
}
int writeInFile(Position p)
{
	FILE* filePointer = NULL;
	filePointer = fopen("ispis.txt", "w");
	if (filePointer == NULL)
	{
		printf("File not is not open!\n");
		return NO_FILE_ERROR;
	}
	p = p->next;
	fprintf(filePointer, "NAME	SURNAME		BIRTH YEAR\n");
	while (p != NULL)
	{
		fprintf(filePointer, "%s	",p->name);
		fprintf(filePointer, "%s	",p->surname);
		fprintf(filePointer, "	%d\n",p->birthYear);
		p = p->next;
	}
	fclose(filePointer);

	return EXIT_SUCCESS;
}

int readFromFile(Position p)
{
	char buffer[MAX_LINE] = {0};
	FILE* filePointer = NULL;
	Position temp = NULL;
	int size = 0,i = 0;
	filePointer = fopen("ispis.txt", "r");
	
	if (filePointer == NULL)
	{
		printf("File not is not open!\n");
		return NO_FILE_ERROR;
	}
	size = noRows();
	temp = p;
	fgets(buffer, MAX_LINE, filePointer);
	for ( i=0;i < size-1;i++)
	{
		Position newPerson = NULL;
		newPerson=(Position)malloc(sizeof(Person));
		fscanf(filePointer,"%s", newPerson->name);
		fscanf(filePointer, "%s", newPerson->surname);
		fscanf(filePointer, "%d", &newPerson->birthYear);
		newPerson->next = temp->next;
		temp->next = newPerson;
		temp= newPerson;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int noRows()
{
	char buffer[MAX_LINE] = { 0 };
	int counter = 0;
	FILE* filePointer = NULL;
	filePointer = fopen("ispis.txt", "r");

	if (filePointer == NULL)
	{
		printf("File not is not open!\n");
		return NO_FILE_ERROR;
	}
	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		counter++;
	}
	//Vraca counter umanjen za 1 zbog prvog reda u datoteci koji nije osoba vec slozi za pojasnjenje unesenih podataka
	return (counter-1);
}
int freeMemory(Position p)
{
	Position temp = NULL;

	while (p->next != NULL)
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}