/* gcc -Wall -O3 -o Ising2D_Ej2b.exe Ising2D_Ej2b.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "FlipBJ.h"

int poblar(int *red, double p, int dim);
int Flip(int* red, int dim, double B, double J, double E, FILE* fpE);

int main()
{
	int *red, dim, muestreos, k;
	double M, B, J, tiempo, E;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
		
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	
	//valores que pide el problema: B = 0, inicializo M = 0 y poblar con p = 0.5
	M = 0.0;
	B = 0.0;
	E = 0.0;
	poblar(red, 0.5, dim);

	FILE* fp;
	FILE* fpE;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filenameE[64];
	char filename[64];
	
	sprintf(filenameE, "EvsJ_dim%i_Barridos%i.txt", dim, muestreos);
	sprintf(filename, "MvsJ_dim%i_Barridos%i.txt", dim, muestreos);
	

	fpE = fopen(filenameE,"w");
	fp = fopen(filename, "w");
		
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	
	tiempo = (double)2*dim*dim*muestreos*50/(double)27716535;
	printf("\nEsto va a tardar aprox %.0lf segundos o %.0lf minutos\n", tiempo ,tiempo/60);
		
	for(J = 0.1; J < 0.6; J = J + 0.01)
	{	
		E = 0.0; 
		fprintf(fp,"%lf\t",J);
		fprintf(fpE,"%lf\t",J);
		for(k = 0; k < muestreos; k++)
		{
			M = Flip(red, dim, B, J, E, fpE);
			fprintf(fp,"%lf\t", M/(dim*dim));
		}
		fprintf(fp,"\n");
		fprintf(fpE,"\n");
		printf("Termine con J = %lf hice %i M's \n", J, k);
	}
	fclose(fp);
	fclose(fpE);
	free(red);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("tiempo = %lf\n", cpu_time_used);
	return 0;
}