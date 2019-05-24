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
int flip_aleatorio(int* red, int dim, int muestreos, double B, double T);


int main()
{
	int *red, dim, pasos, muestreos;
	double p, B, T, M, E, M_prom, Mcuad_prom;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
		
	printf("\nDame una probabilidad para distribuir uniformemente spines up\n");
	scanf("%lf", &p);
	
	printf("\nDame una intensidad de campo magnetico B\n");
	scanf("%lf", &B);
	
	printf("\nDame el numero de veces que queres barrer la red en promedio\n");
	scanf("%i", &pasos);
	
	muestreos = pasos*dim*dim;
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	poblar(red, p, dim);

	FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	if(B < 0)
	{
		sprintf(filename, "MvsT_dim%i_Bneg%.1lf_Pasos_prom%i.txt", dim, -B, pasos);
	}
	else
	{
		sprintf(filename, "MvsT_dim%i_Bpos%.1lf_Pasos_prom%i.txt", dim, B, pasos);
	}
	
	fp = fopen(filename,"w");
	int i = 0;
	for(T = 100; T > 0.01; T = T - 0.1)
	{	
		M = 0;
		for(i = 0; i < 200; i++)
		{
			M += flip_aleatorio(red, dim, muestreos, B, T);
		}
		M_prom = M/(200*dim*dim);
		Mcuad_prom = M*M/(200*dim*dim);
		
		E = -B*M_prom;
		
		printf("Temperatura = %lf\n", T);
		fprintf(fp, "%lf\t", T);
		fprintf(fp, "%lf\t", M_prom); //<M>
		fprintf(fp, "%lf\t", Mcuad_prom); //<M^2>
		fprintf(fp, "%lf\t", M_prom*M_prom); // <M>^2
		fprintf(fp, "%lf\n", E);
	}
	fclose(fp);
	free(red);
	return 0;
}