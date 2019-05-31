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

int main()
{
	int *red, dim, muestreos, promedios, i, k;
	double *mag, *mag_prom, B, T, J, M;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame una temperatura T\n");
	scanf("%lf", &T);
	
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	
	printf("\nDame el numero de promedios\n");
	scanf("%i", &promedios);
	printf("\n\n");
	
	red = (int*)malloc(dim*dim*sizeof(int));
	mag = (double*)malloc(muestreos*sizeof(double));
	mag_prom = (double*)malloc(muestreos*sizeof(double));
	srand(time(NULL));
	
	//valores que pide el problema: B = 0, inicializo M = 0 y poblar con p = 0.5
	
	B = 0.0;
	M = 0.0;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	FILE *fp;
	char filename[64];
	
	sprintf(filename, "CorvsK_dim%i_Pasos%i_prom%i.txt", dim, muestreos, promedios);
	
	fp = fopen(filename, "w");
	
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	poblar(red, 0.5, dim);

	printf("nombre de archivo: %s\n", filename);
	for(J = 0.1; J < 0.6; J = J + 0.01)
	{
		//reinicio mag_prom
		for(i = 0; i < muestreos; i++)
		{
			mag_prom[i] = 0;
		}
		
		for(k = 0; k < promedios; k++)
		{
			for(i = 0; i < muestreos; i++)
			{
				//calculo la magnetización para un dado muestreo.
				M = Flip(red, dim, B, T, J);
				mag[i] = M;
			}
			
			for(i = 0; i < muestreos; i++)
			{
				mag_prom[i] += mag[i]/(double)promedios;
			}
		}
		
		fprintf(fp,"%lf\t", J);
		printf("J = %lf\n", J);
		
		for(i = 0; i < muestreos; i++)
		{
			fprintf(fp,"%lf ", mag_prom[i]);
		}
		fprintf(fp,"\n");
	}
	free(red);
	free(mag);
	free(mag_prom);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("tiempo = %lf\n", cpu_time_used);
	return 0;
}