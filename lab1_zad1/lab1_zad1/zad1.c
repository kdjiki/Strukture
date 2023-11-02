/*
Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)
#define MALLOC_ERROR (-2)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}Student;

int readNoRowsInFile();
int loadingData(int, Student*);
int output(int, Student*);
int relPoints(int, Student*);
Student* memoryAllocation(Student *,int);

int main()
{
	Student* seriesOfStructure = NULL;
	int noRows = 0;
	noRows = readNoRowsInFile();

	printf("%d\n", noRows);
	seriesOfStructure = memoryAllocation(seriesOfStructure,noRows);
	loadingData(noRows, seriesOfStructure);
	output(noRows, seriesOfStructure);
	free(seriesOfStructure);

	return EXIT_SUCCESS;
}

//Funkcija prebrojava redova u datoteci
int readNoRowsInFile()
{
	int counter = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("Student.txt", "r");
	//Ako se datoteka ne uspije otvoriti, program zavrsava i vraca vrijednos -1
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	//Petlja za prebrojavanje redaka
	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		counter++;
	}
	fclose(filePointer);
	return counter;
}

//Funkcija ucitava podatke iz datoteke i sprema ih u niz struktura
int loadingData(int noRows, Student* seriesOfStructure)
{
	FILE* filePointer = NULL;
	int i = 0;

	filePointer = fopen("Student.txt", "r");
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	for (i = 0; i < noRows; i++)
	{
		fscanf(filePointer, "%s", seriesOfStructure[i].name);
		fscanf(filePointer, "%s", seriesOfStructure[i].surname);
		fscanf(filePointer, "%lf", &seriesOfStructure[i].points);
	}
	fclose(filePointer);
	return 0;
}

//Funkcija za izracunavanje relat. br. bodova i ispis podataka
int output(int noRows, Student* seriesOfStructure)
{
	int i = 0,maxPoints=0;
	maxPoints = relPoints(noRows,seriesOfStructure);
	printf("IME PREZIME	BR.BODOVA	RELAT.BR.BODOVA\n");
	for (i = 0; i < noRows; i++)
	{
		printf("%s ", seriesOfStructure[i].name);
		printf("%s	", seriesOfStructure[i].surname);
		printf("%.3lf		", seriesOfStructure[i].points);
		printf("%.3lf\n", seriesOfStructure[i].points / maxPoints * 100);
	}
	return 0;
}

int relPoints(int noRows, Student* seriesOfStructure)
{
	int i=0, maxpoints = 0;

	for (i = 0; i < noRows; i++)
	{
		if (seriesOfStructure[i].points > maxpoints)
		{
			maxpoints = seriesOfStructure[i].points;
		}
	}
	return maxpoints;
}
Student* memoryAllocation(Student* ptr, int n)
{
	ptr = (Student*)malloc(n * sizeof(Student));
	if (ptr == NULL)
	{
		printf("ERROR\n");
		return NULL;
	}
	return ptr;
}