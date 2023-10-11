#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}Student;

int readNorowsInFIle()
{
	int counter = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("Student.txt", "r");
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		counter++;
	}
		fclose(filePointer);
		return counter;
}

int main()
{
	int noRows=0;
	noRows = readNorowsInFIle();

	printf("%d", noRows);

	

	return EXIT_SUCCESS;
}