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
#define MALLOC_ERROR (-2)

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


char menu();
//FUNKCIJE STABLA
positionDirectory makeDirectory(char name[MAX_NAME]);
positionDirectory makeSubdirectory(positionDirectory);
positionDirectory enterInSubdirectory(positionDirectory);
int listDirectory(positionDirectory);
int deleteAllDirectory(positionDirectory);
//FUNKCIJE STOGA
int push(positionStack, positionDirectory);
positionDirectory pop(positionStack);
int deleteStack(positionStack);

int main()
{
	Directory headDirectory = { .name = {0}, .next=NULL, .subDirectory=NULL };
	char function = 0;
	int end = 1;
	positionDirectory root = NULL, currentDirectory=NULL;
	root =makeDirectory("C:");
	headDirectory.next=root;
	currentDirectory = root;
	Stack headStack = {.element=NULL, .next=NULL};
	
	push(&headStack, currentDirectory);

	while(end)
	{
		function = menu();
		switch (function)
		{
		case '1':
			
			currentDirectory->subDirectory=makeSubdirectory(currentDirectory);
			break;
		
		case '2':
			currentDirectory=enterInSubdirectory(currentDirectory);
			if(currentDirectory!=headStack.next)
				push(&headStack, currentDirectory);
			printf("CURRENT IN: %s\n", currentDirectory->name);
			break;
		case '3':
			if (currentDirectory == root)
			{
				printf("You are in the root directory.\n");
				break;
			}
			else
			{
				if (currentDirectory = pop(&headStack)) {
					currentDirectory = headStack.next->element;
					printf("CURRENT IN: %s\n", currentDirectory->name);
				}
				break;
			}
		case '4':
			listDirectory(currentDirectory);
			break;
		case '5':
			printf("END OF PROGRAM");
			deleteAllDirectory(headDirectory.next);
			deleteStack(&headStack);
			end = 0;
			break;
		default:
			if (function <= 49 || function >= 54)
				printf("Wrong input. Try again.\n\n");
			break;
		}
	}
	return EXIT_SUCCESS;
}

char menu()
{
	char character = 0;

	printf("\nTo enter a new directory, enter '1'\nTo enter a subdirectory, enter '2'\nTo return to the previous directory, enter '3'\nTo print the contents of the directory, enter '4'\nTo exit, enter '5'\n");
	scanf(" %c", &character);
	return character;
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
	printf("Insert name of the directory: ");
	scanf("%s",newSubdirectory->name );
	newSubdirectory->next = currentDirectory->subDirectory;
	newSubdirectory->subDirectory = NULL;

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
	positionDirectory tempDirectory = NULL;
	tempDirectory = currentDirectory->subDirectory;
	if (tempDirectory != NULL)
	{
		printf("YOU ARE IN  '%s' DIRECTORY \n", currentDirectory->name);
		printf("This directory contain following subdirectories:\n");
		while (tempDirectory != NULL)
		{
			printf("%s	", tempDirectory->name);
			tempDirectory = tempDirectory->next;
		}
		printf("\n");
	}
	else
		printf("This directory is empty!\n");
	


	return EXIT_SUCCESS;
}
int deleteAllDirectory(positionDirectory headDirectory)
{
	if (headDirectory == NULL)
		return EXIT_SUCCESS;
	deleteAllDirectory(headDirectory->next);
	deleteAllDirectory(headDirectory->subDirectory);
	free(headDirectory);
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
		return MALLOC_ERROR;
	}
	newElement->element = currentDirectory;
	newElement->next = head->next;
	head->next = newElement;

	return EXIT_SUCCESS;
}
positionDirectory pop(positionStack headStack)
{
	positionStack tempElement = NULL;
	positionDirectory currentDirectory=NULL;
	tempElement = headStack->next;
	if (tempElement == NULL)
	{
		printf("Stack is empty.\n");
		return NULL;
	}
	headStack->next = tempElement->next;
	currentDirectory = tempElement->element;
	free(tempElement);
	
	return currentDirectory;
}
int deleteStack(positionStack headStack)
{
	positionStack toDelete = NULL;
	while (headStack->next != NULL)
	{
		toDelete = headStack->next;
		headStack->next = toDelete->next;
		free(toDelete);
	}
	return EXIT_SUCCESS;
}