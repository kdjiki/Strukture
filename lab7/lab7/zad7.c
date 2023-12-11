/*
7. Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME (100)

typedef struct _directory* positionDirectory;
typedef struct _directory {
	char name[MAX_NAME];
	positionDirectory subDirectory;
	positionDirectory next;
}Directory;

typedef struct _stack* positionStack;
typedef struct _stack {
	positionDirectory element;
	positionStack next;
}Stack;


int menu();
//FUNKCIJE STABLA
positionDirectory makeDirectory(char name[MAX_NAME]);
positionDirectory makeSubdirectory(positionDirectory);
positionDirectory enterInSubdirectory(positionDirectory);
int listDirectory(positionDirectory);
//FUNKCIJE STOGA
int push(positionStack, positionDirectory);
positionDirectory pop(positionStack);

int main()
{
	Directory headDirectory = { .name = {0}, .next=NULL, .subDirectory=NULL };
	int function = 0,end=1;
	positionDirectory root = NULL, currentDirectory=NULL;
	root =makeDirectory("C:");
	headDirectory.next=root;
	currentDirectory = root;
	Stack headStack = {.element=NULL, .next=NULL};
	
	push(&headStack, currentDirectory);

	do
	{
		function = menu();
		switch (function)
		{
		case 1:
			
			currentDirectory->subDirectory=makeSubdirectory(currentDirectory);
			break;
		
		case 2:
			currentDirectory=enterInSubdirectory(currentDirectory);
			if(currentDirectory!=headStack.next)
				push(&headStack, currentDirectory);
			printf("CURRENT IN: %s\n", currentDirectory->name);
			break;
		case 3:
			if (currentDirectory == root)
			{
				printf("You are in the root directory.\n");
			}
			else
			{
				currentDirectory = pop(&headStack);
				printf("CURRENT IN: %s\n", currentDirectory->name);
			}
			break;
		case 4:
			listDirectory(currentDirectory);
			break;
		case 5:
			printf("END OF PROGRAM");
			return 0;
			break;
		}
	} while (end);
	return EXIT_SUCCESS;
}

int menu()
{
	int a = 0;
	while (a == 0)
	{
		printf("\nZa unos novog direktorija unesite '1'\nZa ulazak u poddirektorij unesite '2'\nZa povratak u prethodni direktorij unesite '3'\nZa ispis sadrzaja direktorija unesite '4'\nZa izlaz unesite '5'\n");
		scanf("%d", &a);
		if (a <= 0 || a >= 6)
		{
			printf("Wrong input. Try again.\n\n");
			a = 0;
		}
	}
	return a;
}

//FUNKCIJA ZA STABLO

positionDirectory makeDirectory(char name[MAX_NAME])
{
	positionDirectory newDirectory = NULL;
	newDirectory = (positionDirectory)malloc(sizeof(Directory));
	if (newDirectory == NULL)
	{
		printf("ERROR. Memory allocation problem.\n");
		return NULL;
	}
	strcpy(newDirectory->name,name);
	newDirectory->next = NULL;
	newDirectory->subDirectory = NULL;

	return newDirectory;
}

positionDirectory makeSubdirectory(positionDirectory currentDirectory)
{
	positionDirectory newSubdirectory = NULL;
	newSubdirectory = (positionDirectory)malloc(sizeof(Directory));
	char subdirectoryName[MAX_NAME] = { 0 };
	printf("trenutno si u %s\n", currentDirectory->name);
	printf("Insert name of the directory: ");
	scanf("%s",newSubdirectory->name );
	newSubdirectory->next = currentDirectory->subDirectory;
	newSubdirectory->subDirectory = NULL;
	//currentDirectory->subDirectory = newSubdirectory;
	/*scanf("%s", subdirectoryName);
	newSubdirectory=makeDirectory(subdirectoryName);

	newSubdirectory->next = currentDirectory->subDirectory;
	currentDirectory->subDirectory = newSubdirectory;*/

	return newSubdirectory;
}

positionDirectory enterInSubdirectory(positionDirectory currentDirectory)
{
	char subdirectoryName[MAX_NAME] = {0};
	positionDirectory tempDir = currentDirectory->subDirectory;
	printf("Enter the name of the subdirectory you want to enter:\n");
	scanf("%s",subdirectoryName);
	
	while (tempDir != NULL && strcmp(tempDir->name, subdirectoryName) != 0)
	{
		tempDir = tempDir->next;
	}
	if (tempDir == NULL)
	{
		printf("Wrong name. That subdirectory does not exist.\n");
		return currentDirectory;
	}
	else
	{
		currentDirectory = tempDir;
		return currentDirectory;
	}
}
int listDirectory(positionDirectory currentDirectory)
{
	if (currentDirectory->subDirectory != NULL)
	{
		printf("This directory contain following subdirectories:\n");
		while (currentDirectory->subDirectory != NULL)
		{
			printf("%s	", currentDirectory->subDirectory->name);
			currentDirectory->subDirectory = currentDirectory->subDirectory->next;
		}
		printf("\n");
	}
	else
		printf("This directory is empty!\n");

	return EXIT_SUCCESS;
}



//FUNKCIJE ZA STOG

int push(positionStack head, positionDirectory currentDirectory)
{
	positionStack newElement = NULL;

	newElement = (positionStack)malloc(sizeof(Stack));
	if (newElement == NULL)
	{
		printf("ERROR. Memory allocation problem.\n");
		return NULL;
	}
	newElement->element = currentDirectory;
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
positionDirectory pop(positionStack headStack)
{
	//headStack = headStack->next;
	positionStack tempElement = NULL;
	positionDirectory currentDirectory=NULL;
	tempElement = headStack->next;
	if (tempElement==NULL)
	{
		printf("Stack is empty.\n");
		return NULL;
	}
	headStack->next = tempElement->next;
	currentDirectory = tempElement->element;
	free(tempElement);

	return currentDirectory;
}