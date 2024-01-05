/*	8. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/

/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MALLOC_ERROR (-2)
#define FILE_ERROR (-4)

typedef struct _node* Position;
typedef struct _node{
	int element;
	Position left;
	Position right;
}Node;

typedef struct _member* PositionInList;
typedef struct _member {
	Position listElement;
	PositionInList next;
}Member;

char menu();
int check(Position);
Position initialization(Position);
Position insert(Position, int);
int inorder(Position);
int preorder(Position);
int postorder(Position);
int levelOrder(Position);
PositionInList addToTheEnd(PositionInList, Position);
PositionInList deleteList(PositionInList);
Position deleteNode(Position, int);
Position find(Position, int);
Position deleteAll(Position);
int replace(Position);
int leveleOrderInFile(Position, FILE*);
int main()
{
	int end = 1;
	int value = 0, element=0;
	char function = 0;
	Position root = NULL;
	FILE* filePointer = NULL;
	filePointer = fopen("file.txt", "w");
	if (filePointer == NULL)
	{
		printf("Unable to open file.\n");
		return FILE_ERROR;
	}

	while (end) {
		function = menu();
		switch (function)
		{
		case '1':
			printf("\nInsert value:\n");
			scanf("%d", &value);
			root = insert(root, value);
			break;
		case '2':
			//FUNKCIJE check SLUZI ZA PROVJERU JE LI LISTA PRAZNA
			check(root);
			inorder(root);
			break;
		case '3':
			check(root);
			preorder(root);
			break;
		case '4':
			check(root);
			postorder(root);
			break;
		case '5':
			check(root);
			levelOrder(root);
			break;
		case '6':
			printf("Enter element that you want to delete: \n");
			scanf(" %d", &element);
			root = deleteNode(root, element);
			break;
		case '7':
			printf("Enter element that you want to find: \n");
			scanf(" %d", &element);
			find(root, element);
			break;
		case '8':
			check(root);
			replace(root);
			break;
		case '9':
			root=deleteAll(root);
			for (int i = 0; i < 10; i++)
				root = insert(root, random());
			leveleOrderInFile(root, filePointer);
			replace(root);
			leveleOrderInFile(root, filePointer);
			fclose(filePointer);
			break;
		case '0':
			end = 0;
			root=deleteAll(root);
			fclose(filePointer);
			break;
		default:
			//ASCII VRIJEDNOST ZNAKOVA 0 DO 9 JE 48 DO 57
			if (function < 48 || function>57)
				printf("Wrong input! Try again!\n\n");
			break;
		}
	} 
	return EXIT_SUCCESS;
}
char menu()
{
	char function = 0;
	printf("\nEnter '1' to enter the value:\n");
	printf("Enter '2' for inoreder printing:\n");
	printf("Enter '3' for preoreder printing:\n");
	printf("Enter '4' for postoreder printing:\n");
	printf("Enter '5' for leveloreder printing:\n");
	printf("Enter '6' to delete an element:\n");
	printf("Enter '7' to search for an element:\n");
	printf("Enter '8' for opertion %creplace%c;\n", '"','"');
	printf("Enter '9' to enter 10 random values and print them to a file before and after the %creplace%c function is executed: \n", '"', '"');
	printf("Enter '0' to exit\n");

	scanf(" %c", &function);
	return function;
}
int check(Position root)
{
	if (root == NULL)
		printf("THE TREE IS EMPTY!\n");
	return EXIT_SUCCESS;
}
Position initialization(Position newNode)
{
	newNode = (Position)malloc(sizeof(Node));
	if (newNode==NULL)
	{
		printf("ERROR. UNABLE TO ALLOCATE MEMORY\n");
		return NULL;
	}
	newNode->element = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
Position insert(Position root, int value)
{
	if (root == NULL)
	{
		root=initialization(root);
		root->element = value;
	}
	else if (root->element > value) 
		root->left=insert(root->left,value);
	else if (root->element <= value)
		root->right=insert(root->right, value);
	return root;
}
int inorder(Position root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf(" %d", root->element);
		inorder(root->right);
	}
	return EXIT_SUCCESS;
}
int preorder(Position root)
{
	if (root != NULL)
	{
		printf(" %d", root->element);
		preorder(root->left);
		preorder(root->right);
	}
	return EXIT_SUCCESS;
}
int postorder(Position root)
{
	if (root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf(" %d", root->element);
	}
	return EXIT_SUCCESS;
}
int levelOrder(Position root)
{
	if (root != NULL)
	{
		PositionInList head = NULL,temp=NULL;
		head = (PositionInList)malloc(sizeof(Member));
		if (head == NULL)
		{
			printf("ERROR. UNABLE TO ALLOCATE MEMORY\n");
			return NULL;
		}
		head->listElement = root;
		head->next = NULL;
		while (head != NULL) {
			printf("%d ", head->listElement->element);
			if (head->listElement->left != NULL)
				head = addToTheEnd(head, head->listElement->left);
			if (head->listElement->right != NULL)
				head = addToTheEnd(head, head->listElement->right);
			head = head->next;
		}
		head = temp;
		deleteList(head);
	}
	//ISTA PRINCIP RADA SAMO STO JE RED IMPLEMENTIRAN POMOCU NIZA (kao na lab. vjezbama)

	/*Position row[100] = { 0 };
	int first = 0, last = 0;
	row[last++] = root;

	while (first < last) {
		Position current = row[first++];

		printf("%d ", current->element);

		if (current->left != NULL)
			row[last++] = current->left;
		if (current->right != NULL)
			row[last++] = current->right;
	}*/
	return EXIT_SUCCESS;
}
//FUNKCIJA ZA DODAVANJE ELEMENATA NA KRAJ VEZANE LISTE
PositionInList addToTheEnd(PositionInList head, Position newElement)
{
	PositionInList newMember = NULL, first=NULL;
	first = head;
	while (first->next != NULL)
		first = first->next;
	newMember = (PositionInList)malloc(sizeof(Member));
	if (newMember == NULL)
	{
		printf("ERROR. UNABLE TO ALLOCATE MEMORY\n");
		return NULL;
	}
	newMember->listElement = newElement;
	newMember->next = NULL;
	first->next = newMember;
	return head;
}
PositionInList deleteList(PositionInList head)
{
	if (head == NULL)
		return NULL;
	head->next = deleteAll(head->next);
	free(head);
	return NULL;

}
Position deleteNode(Position root, int element)
{
	Position temp = NULL;
	
	if (root == NULL)
		return root;
	else if (root->element > element)
		root->left=deleteNode(root->left, element);
	else if (root->element < element)
		root->right=deleteNode(root->right, element);
	else if (root->element == element)
	{
		if (root->left == NULL)
		{
			temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			temp = root->left;
			free(root);
			return temp;
		}
		else
		{
			temp = root->right;
			while (temp->left != NULL)
				temp = temp->left;
			root->element = temp->element;
			root->right = deleteNode(root->right, temp->element);
		}
	}
	return root;
}
Position find(Position root, int element)
{
	if (root == NULL)
	{
		printf("Element %d does not exist.\n", element);
		return NULL;
	}
	if (root->element == element)
	{
		printf("Element %d exist.\n", element);
		return root;
	}
	if (root->element > element)
		find(root->left,element);
	if (root->element < element)
		find(root->right, element);
	return root;
}
Position deleteAll(Position root)
{
	if (root == NULL)
		return NULL;
	root->left=deleteAll(root->left);
	root->right = deleteAll(root->right);
	free(root);
	return NULL;
}
int replace(Position root)
{
	if (root == NULL)
	{
		return 0;
	}
	int leftElement = 0, rightElement = 0, originalElement=0;
	originalElement = root->element;
	//REKURZIVNI POZIV FUNKCIJE ZA LIJEVO I DESNO DIJETE 
	leftElement = replace(root->left);
	rightElement = replace(root->right);
	root->element = leftElement + rightElement;
	return originalElement + root->element;
}
int random()
{
	int value = 0;
	value = rand() % 81 + 10;
	return value;
}
int leveleOrderInFile(Position root, FILE* filePointer)
{
	if (root != NULL)
	{
		PositionInList head = NULL, temp = NULL;
		head = (PositionInList)malloc(sizeof(Member));
		if (head == NULL)
		{
			printf("ERROR. UNABLE TO ALLOCATE MEMORY\n");
			return NULL;
		}
		head->listElement = root;
		head->next = NULL;
		while (head != NULL) {
			fprintf(filePointer,"%d ", head->listElement->element);
			if (head->listElement->left != NULL)
				head = addToTheEnd(head, head->listElement->left);
			if (head->listElement->right != NULL)
				head = addToTheEnd(head, head->listElement->right);
			head = head->next;
		}
		head = temp;
		deleteList(head);
	}
	fprintf(filePointer,"\n");
	return EXIT_SUCCESS;
}