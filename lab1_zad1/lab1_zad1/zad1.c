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

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}Student;

//Funkcija sluzi za prebrojavanje redova u datoteci
int readNoRowsInFIle()
{
	int counter = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("Student.txt", "r");
	//Ako se datoteka ne uspije otvoriti, program zavrsava
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
void Ucitavanje(int noRows, Student* nizStruktura)
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
		fscanf(filePointer, "%s", nizStruktura[i].name);
		fscanf(filePointer, "%s", nizStruktura[i].surname);
		fscanf(filePointer, "%lf", &nizStruktura[i].points);
	}	
	fclose(filePointer);

}
//Funkcija za izracunavanje relat. br. bodova i ispis podataka
void Ispis(int noRows, Student* nizStruktura)
{
	int i = 0, maxPoints=0;

	for (i = 0; i < noRows; i++)
	{
		if (nizStruktura[i].points > maxPoints)
		{
			maxPoints = nizStruktura[i].points;
		}
	}
	printf("IME PREZIME	BR.BODOVA	RELAT.BR.BODOVA\n");
	for (i = 0; i < noRows; i++)
	{
		printf("%s ", nizStruktura[i].name);
		printf("%s	", nizStruktura[i].surname);
		printf("%.3lf		", nizStruktura[i].points);
		printf("%.3lf\n", nizStruktura[i].points/maxPoints*100);
	}

}


int main()
{
	Student* nizStruktura = NULL;
	int noRows=0;
	noRows = readNoRowsInFIle();

	printf("%d\n", noRows);
	nizStruktura = (Student*)malloc(noRows * sizeof(Student));
	Ucitavanje(noRows, nizStruktura);
	Ispis(noRows, nizStruktura);

	return EXIT_SUCCESS;
}