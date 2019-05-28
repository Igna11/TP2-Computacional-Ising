/* gcc -Wall -O3 -o Ising2D_Ej2b2.exe Ising2D_Ej2b2.c -lm*/

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
	double M, B, T, J, m_suma, m, M2, m2_suma, m2, tiempo;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame la constante de acoplamiento J\n");
	scanf("%lf", &J);
	
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	
	printf("\nDame el numero de promedios\n");
	scanf("%i", &promedios);
	printf("\n\n");
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	
	//valores que pide el problema: B = 0, inicializo M = 0 y poblar con p = 0.5
	M = 0.0;
	M2 = 0.0;
	B = 0.0;
	T = 0.0;
	poblar(red, 0.5, dim);

	FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	
	sprintf(filename, "MvsT_CHI_dim%i_J%.2lf_Pasos%i_prom%i.txt", dim, J, muestreos, promedios);
	
	fp = fopen(filename, "w");
	
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	
	tiempo = (double)dim*dim*promedios*muestreos*1000*2/(double)66597294;
	printf("\nEsto va a tardar aprox %.0lf segundos o %.2lf minutos\n", tiempo ,tiempo/60);
	for(T = 10; T > 0.0; T = T - 0.01)
	{	
		m_suma = 0.0;
		m2_suma = 0.0;
		for(i = 0; i < promedios; i++)
		{
			for(k = 0; k < muestreos; k++)
			{
				M = Flip(red, dim, B, T, J);
				M2 = M*M;
			}
			m_suma += M;
			m2_suma += M2/(dim*dim);
		}
		M = M/(dim*dim); //<M>
		m = m_suma/(dim*dim*promedios); // <M>/N
		m2 = m2_suma/(dim*dim*promedios); // <M^2>/N
		M2 = m*m;//(<M>/N)^2
		fprintf(fp,"%lf\t%lf\t%lf\t%lf\t%lf\n", T, M, m, m2, M2);
		printf("T = %lf\t <M> = %.2lf\t <M>/N = %lf\t <M^2>/N = %lf\t (<M>/N)^2 = %lf\n", T, M, m, m2, M2);
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