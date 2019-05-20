/* gcc -Wall -O3 -o Ising2D_Ej2a.exe Ising2D_Ej2a.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "Imprimir.h"

int poblar(int *red, double p, int dim);
int imprimir(int* red, int dim);

int main()
{
	int dim, *red;
	double p;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame una probabilidad para distribuir uniformemente spines up\n");
	scanf("%lf", &p);
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(1);
	poblar(red, p, dim);
	imprimir(red, dim);
	return 0;
}