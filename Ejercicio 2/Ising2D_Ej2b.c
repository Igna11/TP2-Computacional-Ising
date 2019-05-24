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
	int *red, dim, muestreos,i ;
	double M, B, T, J, m_suma, m;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
	
	printf("\nDame una temperatura T\n");
	scanf("%lf", &T);
	
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	printf("\n\n");
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	
	//valores que pide el problema: B = 0, inicializo M = 0 y poblar con p = 0.5
	M = 0.0;
	B = 0.0;	
	poblar(red, 0.5, dim);

	FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	
	sprintf(filename, "MvsJ_dim%i_T%.2lf_Pasos_prom%i.txt", dim, T, muestreos);
	
	fp = fopen(filename, "w");
	
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	
	for(J = 0.1; J < 0.6; J = J + 0.0005)
	{	
		m_suma = 0.0;
		for(i = 0; i < 200; i++)
		{
			M = Flip(red, dim, muestreos, B,T,J);
			m_suma += M;
		}
		m = m_suma/(dim*dim*200);
		fprintf(fp,"%lf\t%lf\n",J,m);
		printf("J = %lf\t M = %lf\n", J,m);
		
	}
	fclose(fp);
	free(red);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("tiempo = %lf\n", cpu_time_used);
	return 0;
}