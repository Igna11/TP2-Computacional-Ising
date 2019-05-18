/* gcc -Wall -O3 -o IS_1a_1.exe ImportanceSamplingEj1A_1.c -lm*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Muestreo_d.h"
#include "Normal_d.h"

double Muestreo(int iteraciones, int aceptacion, double* vec, double x0, double delta);

int main()
{
	double x0, delta, delta_i, delta_f, *vec, porcentaje;
	int iteraciones, aceptacion;
		
	printf("dame un x0\n");
	scanf("%lf",&x0);

	printf("dame un delta inicial\n");
	scanf("%lf",&delta_i);
	
	printf("dame un delta final\n");
	scanf("%lf",&delta_f);
	
	printf("dame el numero de iteraciones que queres\n");
	scanf("%i", &iteraciones);
	
	vec = (double*)malloc(iteraciones*sizeof(double));
	
	srand(1);

	/*
	EXPORTA EL PORCENTAJE DE ACEPTACIÓN EN FUNCIÓN DEL DELTA. --> EJ 1)a)
	*/
	FILE* fp;
	fp = fopen("IMP-SAMP-ACEPTvsDELTA.txt","w");
	srand(1);
	for(delta = delta_i; delta < delta_f; delta = delta + 0.1)
	{
		
		aceptacion = 0; // reinicio aceptacion
		
		aceptacion = Muestreo(iteraciones, aceptacion, vec, x0, delta); //veo cuantos acepto
		
		porcentaje = (double)aceptacion/(double)iteraciones; //lo escribo como porcentaje
		
		printf("delta = %f\t", delta);
		printf("porcentaje = %f\n", porcentaje);
		
		fprintf(fp,"%f\t", delta);
		fprintf(fp,"%f\n", porcentaje);
	}
	
	
	free(vec);
	return 0;
}