/* gcc -Wall -O3 -o Ising2D_Ej2b.exe Ising2D_Ej2b.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "Imprimir.h"
#include "FlipBJ.h"

int poblar(int *red, double p, int dim);
int imprimir(int* red, int dim);
int Flip(int* red, int dim, int muestreos, double B, double T, double J);

int main()
{
	//int i, j, k;
	int *red, dim, muestreos;
	double p, B, T, J;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
		
	printf("\nDame una probabilidad para distribuir uniformemente spines up\n");
	scanf("%lf", &p);
	
	printf("\nDame una intensidad de campo magnetico B\n");
	scanf("%lf", &B);
	
	printf("\nDame una intensidad del acoplamiento J\n");
	scanf("%lf", &J);
	
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	printf("\n\n");
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	
	FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	
	sprintf(filename, "JyB_MvsT_dim%i_J%.1lf_B%.1lf_Pasos%i.txt", dim,J, B, muestreos);
	
	double M = 0.0;
	
	fp = fopen(filename, "w");
	poblar(red, p, dim);
	
	for(T = 10; T > 0.00001; T = T - 0.01)
	{	
		//imprimir(red, dim);
		M = Flip(red, dim, muestreos, B,T,J);
		
		fprintf(fp,"%lf\t%lf\n",T,M);
		printf("T = %lf\t M = %lf\n", T,M);
		//printf("\n");
		//imprimir(red, dim);
	}
	fclose(fp);
	free(red);

	return 0;
}