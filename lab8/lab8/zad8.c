/*	8. Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i
level order), brisanje i pronalaženje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MALLOC_ERROR (-2)

typedef struct _node* Position;
typedef struct _node{
	int element;
	Position left;
	Position right;
}Node;

char menu();
Position initialization(Position);
Position input(Position, int);
int inorder(Position);
int preorder(Position);
int postorder(Position);
Position deleteNode(Position, int);
Position find(Position, int);
Position deleteAll(Position);
int main()
{
	int end = 1;
	int value = 0, element=0;
	char function = 0;
	Position root = NULL;

	while (end) {
		function = menu();
		switch (function)
		{
		case '1':
			printf("\nInsert value:\n");
			scanf("%d", &value);
			root=input(root,value);
			break;
		case '2':
			inorder(root);
			break;
		case '3':
			preorder(root);
			break;
		case '4':
			postorder(root);
			break;
		case '5':
			break;
		case '6':
			printf("Enter element that you want to delete: \n");
			scanf(" %d", &element);
			root=deleteNode(root,element);
			break;
		case '7':
			printf("Enter element that you want to find: \n");
			scanf(" %d",&element);
			find(root, element);
			break;
		case '8':
			end = 0;
			deleteAll(root);
			break;
		default:
			if (function < 49 || function>56)
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
	printf("Enter '8' to exit\n");
	scanf(" %c", &function);

	return function;
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
Position input(Position root, int value)
{
	if (root == NULL)
	{
		root=initialization(root);
		root->element = value;
	}
	else if (root->element>value) 
		root->left=input(root->left,value);
	else if (root->element < value)
		root->right=input(root->right, value);
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