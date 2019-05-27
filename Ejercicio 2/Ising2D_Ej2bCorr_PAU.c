/* gcc -Wall -O3 -o Ising2D_Ej2bCorr.exe Ising2D_Ej2bCorr.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "FlipBJ.h"
#include "MedVal_d.h"
#include "M_corr_pau.h"


int poblar(int *red, double p, int dim);
int Flip(int* red, int dim, double B, double T, double J);
double M_corr_pau(double* mag, double* c_k, int* red, int dim, double B, double T, double J, int muestreos, int k_max);


int main()
{
	int *red, dim, muestreos, promedios, i, k, k_max;
	double *mag, *c_k, *c_kprom, B, T, J;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame una temperatura T\n");
	scanf("%lf", &T);
	
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	
	printf("\nDame el numero de promedios\n");
	scanf("%i", &promedios);
	printf("\n\n");
	
	k_max = muestreos/2;
	
	red = (int*)malloc(dim*dim*sizeof(int));
	mag = (double*)malloc(muestreos*sizeof(double));
	c_k = (double*)malloc(k_max*sizeof(double));
	c_kprom = (double*)malloc(k_max*sizeof(double));
	srand(time(NULL));
	
	//valores que pide el problema: B = 0, inicializo M = 0 y poblar con p = 0.5
	
	B = 0.0;	
	poblar(red, 0.5, dim);

	//FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	//char filename[64];
	
	//sprintf(filename, "CorvsK_dim%i_Pasos%i_prom%i.txt", dim, muestreos, promedios);
	
	//fp = fopen(filename, "w");
	
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	
	for(J = 0.1; J < 0.6; J = J + 0.001)
	{	
		//fprintf(fp,"%lf\t", J);
		printf("J = %lf\n", J);
		
		k = 0;
		//limpio c_k y c_kprom
		for(k = 0; k < k_max; k++)
		{
			c_kprom[k] = 0;
			c_k[k] = 0;
			//printf("indice %i borro\n", k);
		}
		
		for(i = 0; i < promedios; i++)
		{
			M_corr_pau(mag, c_k, red, dim, B, T, J, muestreos, k_max);
		
			for(k = 0; k < k_max; k++)
			{
			//fprintf(fp,"%lf ", c_kprom[k]);
				printf("c_k[%i] = %lf\t ", k, c_k[k]);
			}
			/*
			for(k = 0; k < k_max; k++)
			{
				c_kprom[k] += c_k[k];
			}
			*/
		}
		
		
		//fprintf(fp,"\n");
		//printf("\n");
	}
	//fclose(fp);
	free(red);
	free(mag);
	free(c_k);
	free(c_kprom);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("tiempo = %lf\n", cpu_time_used);
	return 0;
}