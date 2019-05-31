/* gcc -Wall -O3 -o Ising2D_Ej2e.exe Ising2D_Ej2e.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "Imprimir.h"
#include "FlipBJ2.h"

int poblar(int *red, double p, int dim);
int imprimir(int* red, int dim);
int Flip(int* red, int dim, double B, double T, double J);

int main()
{
	int *red, dim, muestreos, promedios, i, k;
	double M, B, T, J, m_suma, m, tiempo;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame una temperatura T\n");
	scanf("%lf", &T);
	
	printf("\nDame el campo B\n");
	scanf("%lf", &B);
	
	printf("\nDame el acoplamiento J\n");
	scanf("%lf", &J);
	
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	
	printf("\nDame el numero de promedios\n");
	scanf("%i", &promedios);
	printf("\n\n");
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	
	//valores que pide el problema: B = 0, inicializo M = 0 y poblar con p = 0.5
	poblar(red, 0.5, dim);

	/*
	FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	
	sprintf(filename, "MvsJ_dim%i_T%.2lf_B%.2lf_J%.2lf_Pasos%i_prom%i.txt", dim, T, B, J, muestreos, promedios);
	
	fp = fopen(filename, "w");
	*/
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	M = 0.0;
	tiempo = (double)2*dim*dim*promedios*muestreos*500/(double)200000000;
	printf("\nEsto va a tardar aprox %.0lf segundos o %.0lf minutos\n", tiempo ,tiempo/60);
	for(J = 0.1; J < 0.6; J = J + 0.001)
	{	
		m_suma = 0.0;
		for(i = 0; i < promedios; i++)
		{
			for(k = 0; k < muestreos; k++)
			{
				M = Flip(red, dim, B, T, J);
			}
			m_suma += M;
		}
		m = m_suma/(dim*dim*promedios);
		M = M/(dim*dim);
		//fprintf(fp,"%lf\t%lf\t%.20lf\n", J, M, m);
		printf("J = %lf\t M = %.2lf\t M_prom = %lf\n", J, M, m);
	}
	//fclose(fp);
	free(red);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("tiempo = %lf\n", cpu_time_used);
	return 0;
}