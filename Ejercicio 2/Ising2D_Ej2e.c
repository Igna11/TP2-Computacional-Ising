/* gcc -Wall -O3 -o Ising2D_Ej2e.exe Ising2D_Ej2e.c -lm*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Poblar.h"
#include "FlipBJ2.h"

int poblar(int *red, double p, int dim);
int Flip(int* red, int dim, double B, double J, double E_suma, double* E);

int main()
{
	int *red, dim, muestreos, k, tau, i;
	double M, B, J, tiempo, E_suma, *E;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
		
	printf("\nDame el numero de veces que queres barrer la red\n");
	scanf("%i", &muestreos);
	
	printf("\nDame el tau\n");
	scanf("%i", &tau);
	
	printf("\nDame B\n");
	scanf("%lf",&B);
	
	red = (int*)malloc(dim*dim*sizeof(int));
	
	srand(time(NULL));
	
	//valores que pide el problema: inicializo M = 0 y poblar con p = 0.5
	M = 0.0;
	E_suma = 0.0;
	E = (double*)malloc(1*sizeof(double));
	poblar(red, 0.5, dim);

	FILE* fp;
	FILE* fpE;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filenameE[64];
	char filename[64];
	
	sprintf(filenameE, "Item_e_EvsJ_dim%i_Barridos%i_tau%i_B%.2lf.txt", dim, muestreos, tau, B);
	sprintf(filename, "Item_e_MvsJ_dim%i_Barridos%i_tau%i_B%.2lf.txt", dim, muestreos, tau, B);
	

	fpE = fopen(filenameE,"w");
	fp = fopen(filename, "w");
		
	//para medir el tiempo
	clock_t start, end;
	double cpu_time_used;
    start = clock();
	
	tiempo = (double)2*dim*dim*muestreos*tau*200/(double)15641025;
	printf("\nEsto va a tardar aprox %.0lf segundos o %.0lf minutos\n", tiempo ,tiempo/60);
	for(J = 1.0; J >= -1.0; J = J - 0.01)
	{	
		printf("J = %lf\n",J);
		//reinicio E_suma
		E_suma = 0.0;
		fprintf(fp,"%lf\t",J);
		fprintf(fpE,"%lf\t",J);
		for(i = 0; i< muestreos; i++)
		{
			for(k = 0; k < tau; k++)
			{
				M = Flip(red, dim, B, J, E_suma, E);
			}
			fprintf(fp,"%lf ", M/(dim*dim));
			fprintf(fpE,"%lf ", E[0]);
		}
		fprintf(fp,"\n");
		fprintf(fpE,"\n");
		printf("Termine con J = %lf hice %i M's \n", J, i);
	}
	fclose(fp);
	fclose(fpE);
	free(red);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("tiempo = %lf\n", cpu_time_used);
	printf("\n%s\n",filenameE);
	printf("\n%s\n",filename);
	return 0;
}