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
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}Student;

int PrebrojiRedove();
void Ucitavanje(int, Student*);
void Ispis(int, Student*);

int main()
{
	Student* nizStruktura = NULL;
	int BrRedova=0;
	BrRedova = PrebrojiRedove();

	printf("%d\n", BrRedova);
	nizStruktura = (Student*)malloc(BrRedova * sizeof(Student));
	Ucitavanje(BrRedova, nizStruktura);
	Ispis(BrRedova, nizStruktura);

	return EXIT_SUCCESS;
}

//Funkcija prebrojava redova u datoteci
int PrebrojiRedove()
{
	int brojac = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("C:\\Users\\Kreso\\.ssh\\Strukture\\lab1_zad1\\lab1_zad1\\Student.txt", "r");
	//Ako se datoteka ne uspije otvoriti, program zavrsava i vraca vrijednos -1
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	//Petlja za prebrojavanje redaka
	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		brojac++;
	}
	fclose(filePointer);
	return brojac;
}

//Funkcija ucitava podatke iz datoteke i sprema ih u niz struktura
void Ucitavanje(int noRows, Student* nizStruktura)
{
	FILE* filePointer = NULL;
	int i = 0;

	filePointer = fopen("C:\\Users\\Kreso\\.ssh\\Strukture\\lab1_zad1\\lab1_zad1\\Student.txt", "r");
	if (!filePointer) {
		printf("File is not open!\n");
		return FILE_ERROR_OPEN;
	}

	for (i = 0; i < noRows; i++)
	{
		fscanf(filePointer, "%s", nizStruktura[i].ime);
		fscanf(filePointer, "%s", nizStruktura[i].prezime);
		fscanf(filePointer, "%lf", &nizStruktura[i].bodovi);
	}
	fclose(filePointer);
}

//Funkcija za izracunavanje relat. br. bodova i ispis podataka
void Ispis(int BrRedova, Student* nizStruktura)
{
	int i = 0, maxBod = 0;

	for (i = 0; i < BrRedova; i++)
	{
		if (nizStruktura[i].bodovi > maxBod)
		{
			maxBod = nizStruktura[i].bodovi;
		}
	}
	printf("IME PREZIME	BR.BODOVA	RELAT.BR.BODOVA\n");
	for (i = 0; i < BrRedova; i++)
	{
		printf("%s ", nizStruktura[i].ime);
		printf("%s	", nizStruktura[i].prezime);
		printf("%.3lf		", nizStruktura[i].bodovi);
		printf("%.3lf\n", nizStruktura[i].bodovi / maxBod * 100);
	}

}
