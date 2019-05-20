/* gcc -Wall -O3 -o Ising2D_Ej2a.exe Ising2D_Ej2a.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "Imprimir.h"
#include "Flip_aleatorio.h"

int poblar(int *red, double p, int dim);
int imprimir(int* red, int dim);
int flip_aleatorio(int* red, int dim, int pasos, double B, double T);


int main()
{
	int dim, *red, pasos;
	double p, B, T;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame una probabilidad para distribuir uniformemente spines up\n");
	scanf("%lf", &p);
	
	printf("\nDame una intensidad de campo magnetico B\n");
	scanf("%lf", &B);
	
	printf("\nDame el numero de veces que queres barrer la red en promedio\n");
	scanf("%i", &pasos);
	
	pasos = pasos*dim;
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	T = 0.5;
	srand(1);
	poblar(red, p, dim);
	imprimir(red, dim);
	flip_aleatorio(red, dim, pasos, B, T);
	imprimir(red, dim);
	return 0;
}