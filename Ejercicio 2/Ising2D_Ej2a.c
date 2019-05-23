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
int flip_aleatorio(int* red, int dim, int muestreos, int len_mag, double *mag, double B, double T);


int main()
{
	int *red, dim, pasos, muestreos, len_mag, i;
	double *mag, p, B, T, M, E, M_suma, M_mean;
	
	printf("\nDame dimension de la red\n");
	scanf("%i", &dim);
		
	printf("\nDame una probabilidad para distribuir uniformemente spines up\n");
	scanf("%lf", &p);
	
	printf("\nDame una intensidad de campo magnetico B\n");
	scanf("%lf", &B);
	
	printf("\nDame el numero de veces que queres barrer la red en promedio\n");
	scanf("%i", &pasos);
	
	muestreos = pasos*dim*dim;
	
	//len_mag es la longitud de mag. Mag es un vector que pretende guardar el 10% de los últimos datos adquiridos de magnetización, 
	//suponiendo que ya el sistema está en regimen, estacionaria en el 100% de los pasos(ya en régimen estacionario)
	//si fueran 1000 pasos, len mag va a guardar desde el paso 900 hasta el 1000 las diferentes magnetizaciones. Así se pueden promediar.
	len_mag = muestreos/10;
	
	red = (int*)malloc(dim*dim*sizeof(int));
	mag = (double*)malloc(len_mag*sizeof(double));
	
	srand(time(NULL));
	poblar(red, p, dim);

	FILE* fp;
	
	//forma cool de definir el nombre del .txt, para favorecer orden
	char filename[64];
	if(B < 0)
	{
		sprintf(filename, "MvsT_dim%i_Bneg%.1lf_Pasos%i.txt", dim, -B, pasos);
	}
	else
	{
		sprintf(filename, "MvsT_dim%i_Bpos%.1lf_Pasos%i.txt", dim, B, pasos);
	}
	
	fp = fopen(filename,"w");
	for(T = 100; T > 0.01; T = T - 0.1)
	{
		//lleno de 0 el vector mag
		for(i = 0; i < len_mag; i++){
			mag[i] = 0.0;
		}
		
		M = flip_aleatorio(red, dim, muestreos, len_mag, mag, B, T);
		M = M/(dim*dim);
		
		M_suma = 0.0;
		
		
		for(i = 0; i < len_mag; i++){
			M_suma += mag[i];
		}
		M_mean = M_suma/(double)len_mag;
		
		E = -B*M;
		printf("Temperatura = %lf\n", T);
		fprintf(fp, "%lf\t", T);
		fprintf(fp, "%lf\t", M);
		fprintf(fp, "%lf\t", M_mean);
		fprintf(fp, "%lf\n", E);
	}
	fclose(fp);
	free(red);
	free(mag);
	return 0;
}