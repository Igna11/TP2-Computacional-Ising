/* gcc -Wall -O3 -o Ising2D_Ej2d.exe Ising2D_Ej2d.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "Imprimir.h"
#include "FlipBJ.h"

int poblar(int *red, double p, int dim);
int imprimir(int* red, int dim);
int Flip(int* red, int dim, double B, double T, double J);

int main()
{
	int *red, dim, muestreos, promedios, i, k;
	double M, B, T, J, m_suma, m;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame el campo B\n");
	scanf("%lf", &B);
	
	printf("\nDame el acoplamientoJ\n");
	scanf("%lf", &J);
	
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	
	printf("\nDame el numero de promedios\n");
	scanf("%i", &promedios);
	printf("\n\n");
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	
	M = 0.0;
	poblar(red, 0.5, dim);

	FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	
	sprintf(filename, "Antiferro_dim%i_B%.2lf_J%.2lf_Pasos%i_prom%i.txt", dim, B, J, muestreos, promedios);
	
	fp = fopen(filename, "w");
	
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	double tiempo = (double)2*dim*dim*promedios*muestreos*500/(double)81500000;
	printf("\n Esto va a tardar aprox %.0lf segundos o %.0lf minutos\n\n", tiempo, tiempo/60);

	for(T = 50; T > 0; T = T - 0.1)
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
		m = m_suma/(dim*dim*promedios); //promediados
		M = M/(dim*dim); // crudos
		fprintf(fp,"%lf\t%lf\t%.20lf\n", T, M, m);
		printf("T = %lf\t M = %.2lf\t M_prom = %lf\n", T, M, m);
	}
	fclose(fp);
	free(red);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	double trabajo = (double)dim*dim*2*promedios*muestreos*500/cpu_time_used;
	
	printf("aproximadamente %.0lf iteraciones en\n", (double)dim*dim*2*promedios*muestreos*500);
	printf("tiempo = %lf\n", cpu_time_used);
	printf("Son entonces %.0lf iteraciones por segundo\n", trabajo);
	printf("el archivo se llama %s\n", filename);
	return 0;
}