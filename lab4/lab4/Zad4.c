/*
4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE (1024)
#define MALLOC_ERROR (NULL)
#define FILE_ERROR (-1)
#define EMPTY_LIST (2)
#define FILE_SHAPE_ERROR (3)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element {
	int Exp;
	int Coeff;
	Position Next;
}Element;

Position initialization(Position);
int readFile(Position,Position);
int printPoly(Position);
int scanInList(Position, int, int);
int sumPoly(Position,Position,Position);
int multiPoly(Position,Position,Position);
int sort(Position);
int deleteAll(Position );

int main()
{
	Position headPoly1 = NULL;
	Position headPoly2 = NULL;
	Position headPolySum = NULL;
	Position headPolyMulti = NULL;
	
	//Postavlja head liste na pocetne vrijednosti
	headPoly1=initialization(headPoly1);
	headPoly2=initialization(headPoly2);
	headPolySum=initialization(headPolySum);
	headPolyMulti=initialization(headPolyMulti);

	readFile(headPoly1,headPoly2);
	printf("First polynome: ");
	printPoly(headPoly1->Next);
	printf("Second polynome: ");
	printPoly(headPoly2->Next);

	sumPoly(headPoly1,headPoly2,headPolySum);
	printf("\nSum of polynomials: ");
	printPoly(headPolySum->Next);

	multiPoly(headPoly1->Next, headPoly2->Next, headPolyMulti);
	printf("Product of polynomials:");
	printPoly(headPolyMulti->Next);
	
	deleteAll(headPoly1);
	deleteAll(headPoly2);
	deleteAll(headPolySum);
	deleteAll(headPolyMulti);
	
	return EXIT_SUCCESS;
}

Position initialization(Position p)
{
	p = (Position)malloc(sizeof(Element));
	if (p==NULL)
	{
		printf("ERROR.Unable to allocate memory.\n");
		return MALLOC_ERROR;
	}

	p->Coeff = 0;
	p->Exp = 0;
	p->Next = NULL;

	return p;
}

int readFile(Position hp1, Position hp2)
{
	char buffer[MAX_LINE] = {0};
	int tempBuff = 0, tempExp=0,tempCoef=0, bufferCounter=0;
	FILE* filePointer = NULL;
	filePointer = fopen("polynomials.txt","r");
	//Provjera je li file uspjesno otvoren
	if (filePointer == NULL)
	{
		printf("ERROR.Unable to open file.\n");
		return FILE_ERROR;
	}
	//Spremanje prvog polinoma
	fgets(buffer, MAX_LINE,filePointer);
	while (sscanf(buffer + tempBuff, "%dx^%d %n", &tempCoef, &tempExp, &bufferCounter) == 2)
	{
		//tempBuff sluzi za pomjeranje pokazivaca i citanje iduceg clana polinoma sve daok ne dodemo do kraja
		tempBuff += bufferCounter;
		scanInList(hp1,tempCoef,tempExp);
	}
	//Spremanje drugog polinoma
	fgets(buffer, MAX_LINE, filePointer);
	tempBuff = 0;
	while (sscanf(buffer + tempBuff, "%dx^%d %n", &tempCoef, &tempExp, &bufferCounter) == 2)
	{
		tempBuff += bufferCounter;
		scanInList(hp2, tempCoef, tempExp);
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}

int scanInList(Position p, int coef, int exp)
{
	Position newElement = NULL,temp=NULL;
	//Spremanje po velicini(od najveceg prema najmanjem)
	while (p->Next != NULL && p->Next->Exp>exp) {
		p = p->Next;
	}
	if (p->Next==NULL || p->Next->Exp<exp) {
		//Ucitavanje novog elementa u listi i povezivanje s ostatkom liste
		newElement = initialization(newElement);
		newElement->Coeff = coef;
		newElement->Exp = exp;
		newElement->Next = p->Next;
		p->Next = newElement;
	}
	else
	{
		//Ako vec postoji clan s unesenim eksponentom
		p->Next->Coeff += coef;
		//Ako se dogodi da zbroj koeficijenta bude 0 brise se taj element
		if (p->Next->Coeff == 0)
		{
			temp = p->Next->Next;
			free(p->Next);
			p->Next=temp;
		}
	}

	return EXIT_SUCCESS;
}

int printPoly(Position p)
{
	//Provjera je li lista prazna
	if (p == NULL)
	{
		printf("ERROR. Empty list.");
		return EMPTY_LIST;
	}

	while (p->Next!= NULL)
	{
		if (p->Coeff < 0) {
			//Ako je koeficijen negativan stavljamo ga u zagrade
			printf("(%dx^%d)+", p->Coeff, p->Exp);
			p = p->Next;
		}
		else if (p->Exp == 0)
		{
			//Ako je eksponent jednak 0 ispisujemo samo koeficijen jer je x^0=1
			printf("%d+", p->Coeff);
			p = p->Next;
		}
		else
		{
			//Inace ispisujemo u normalnom obliku do predzadnjeg clana
			printf("%dx^%d+", p->Coeff, p->Exp);
			p = p->Next;
		}
	}
	//zadnji clan ispisujemo posebno kako ne bismo imali + na kraju polinoma
	printf("%dx^%d\n", p->Coeff, p->Exp);
	return EXIT_SUCCESS;
}
int sumPoly(Position p1, Position p2, Position pSum)
{
	Position newElement = NULL;

	while (p1->Next != NULL && p2->Next!=NULL)
	{
		if (p1->Next->Exp > p2->Next->Exp)
		{
			newElement = initialization(newElement);
			newElement->Coeff = p1->Next->Coeff;
			newElement->Exp = p1->Next->Exp;
			//"Dodaj na kraj liste"
			while (pSum->Next !=NULL)
				pSum = pSum->Next;
			newElement->Next = pSum->Next;
			pSum->Next = newElement;
			//p1 pomjeramo za jedno mjesto jer smo upisali element iz p1
			p1 = p1->Next;
		}
		else if (p1->Next->Exp < p2->Next->Exp)
		{
			newElement = initialization(newElement);
			newElement->Coeff = p2->Next->Coeff;
			newElement->Exp = p2->Next->Exp;
			while (pSum->Next != NULL)
				pSum = pSum->Next;
			newElement->Next = pSum->Next;
			pSum->Next = newElement;
			//p2 pomjeramo za jedno mjesto jer smo upisali element iz p2
			p2 = p2->Next;
		}
		else if(p1->Next->Exp == p2->Next->Exp)
		{
			newElement = initialization(newElement);
			newElement->Coeff = p2->Next->Coeff+p1->Next->Coeff;
			newElement->Exp = p2->Next->Exp;
			while (pSum->Next != NULL)
				pSum = pSum->Next;
			newElement->Next = pSum->Next;
			pSum->Next = newElement;
			//Pomjeramo i p1 i p2 jer smo upisali oba elementa
			p1 = p1->Next;
			p2 = p2->Next;
		}
	}
	//Petlja se izvodi u slucaju ako je p2 kraci od p1
	if (p1->Next != NULL)
	{
		while (p1->Next != NULL)
		{
			newElement = initialization(newElement);
			newElement->Coeff = p1->Next->Coeff;
			newElement->Exp = p1->Next->Exp;
			while (pSum->Next != NULL)
				pSum = pSum->Next;
			newElement->Next = pSum->Next;
			pSum->Next = newElement;
			p1 = p1->Next;
		}
	}
	//Petlja se izvodi u slucaju ako je p1 kraci od p2
	if (p2->Next != NULL)
	{
		while (p2->Next != NULL)
		{
			newElement = initialization(newElement);
			newElement->Coeff = p2->Next->Coeff;
			newElement->Exp = p2->Next->Exp;
			while (pSum->Next != NULL)
				pSum = pSum->Next;
			newElement->Next = pSum->Next;
			pSum->Next = newElement;
			p2 = p2->Next;
		}
	}
	return EXIT_SUCCESS;
}
int multiPoly(Position p1, Position p2, Position pMulti)
{
	Position newElement = NULL;
	Position temp = NULL;
	temp = p2;
	//Mnozenje "svaki sa svakim"
	while (p1 != NULL)
	{
		while (p2 != NULL) {
			newElement = initialization(newElement);
			newElement->Exp = p1->Exp + p2->Exp;
			newElement->Coeff = p1->Coeff * p2->Coeff;
			newElement->Next = pMulti->Next;
			pMulti->Next = newElement;
			p2 = p2->Next;
		}
		p2 = temp;
		p1 = p1->Next;
	}
	//Sortiranje dobivene liste
	sort(pMulti);
	return EXIT_SUCCESS;
}
int sort(Position p)
{
	Position j, prev_j, temp, end, i=NULL;
	//Bubble sort
	end = NULL;
	while (p->Next != end)
	{
		prev_j = p;
		j = p->Next;
		while (j->Next != end)
		{
			if (j->Exp < j->Next->Exp)
			{
				temp = j->Next;
				prev_j->Next = temp;
				j->Next = temp->Next;
				temp->Next = j;
				j = temp;
			}
			prev_j = j;
			j = j->Next;
		}
		end = j;
	}
	//U slucaju ako se pojavi vise elemenata s istim eksponentom reduciramo njihov broj kao i kod unosa
	i = initialization(i);
	while (p->Next->Next != NULL)
	{
		i = p->Next;
		if (i->Exp == i->Next->Exp)
		{
			temp = i->Next;
			i->Coeff += temp->Coeff;
			i->Next = temp->Next;
			free(temp);
		}
		p = p->Next;
		
	}
	return EXIT_SUCCESS;
}

int deleteAll(Position p)
{
	Position temp = NULL;
	while (p ->Next!= NULL)
	{
		temp = p->Next;
		p->Next = temp->Next;
		free(temp);
	}
	free(p);

	return EXIT_SUCCESS;
}