/* gcc -Wall -O3 -o Ising2D_Ej2bCorr.exe Ising2D_Ej2bCorr.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "Imprimir.h"
#include "FlipBJ.h"
#include "MedVal_d.h"
#include "M_corr.h"

int poblar(int *red, double p, int dim);
int imprimir(int* red, int dim);
int Flip(int* red, int dim, double B, double T, double J);
double M_corr(double* mag, double* c_k, int* red, int dim, double B, double T, double J, int muestreos, int k_max);

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

	
	/*forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	
	sprintf(filename, "CorvsK_dim%i_Pasos%i_prom%i.txt", dim, muestreos, promedios);
	
	fp = fopen(filename, "w")*/
	
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	
	for(J = 0.1; J < 0.2; J = J + 0.1)
	{	
		//limpio c_k y c_kprom
		for(k = 0; k < k_max; k++)
		{
			c_kprom[k] = 0;
			c_k[k] = 0;
		}
		
		for(i = 0; i < promedios; i++)
		{
			M_corr(mag, c_k, red, dim, B, T, J, muestreos, k_max);
			
			for(k = 0; k < k_max; k++)
			{
				c_kprom[k] += c_k[k];
			}
		}
	}

	free(red);
	free(mag);
	free(c_k);
	free(c_kprom);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("tiempo = %lf\n", cpu_time_used);
	return 0;
}