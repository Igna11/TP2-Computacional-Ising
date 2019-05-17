/*gcc -Wall -O3 -o IS_a.exe ImportanceSampling.c -lm*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Muestreo.h"
#include "Normal.h"

float Muestreo(int iteraciones, int aceptacion, float* vec, float x0, float delta);
float Normal(float x0);

int main()
{
	float x0, delta;
	double porcentaje;
	int iteraciones, aceptacion;
	float *vec;
	
	//FILE* fp;
	
	printf("\n\ndame un x0\n\n");
	scanf("%f",&x0);

	printf("\n\ndame un delta\n\n");
	scanf("%f",&delta);
	
	printf("\n\ndame el numero de iteraciones que queres\n\n");
	scanf("%i", &iteraciones);
	
		
	vec = (float*)malloc(iteraciones*sizeof(float));
		
	aceptacion = 0;
		
	//fp = fopen("Is_a_float.txt","w");
	
	//////////////////// ACA VA LA FUNCIÓN /////////////////////////
	///ACA HICE LA FUNCIÓN PARA SACAR EL PORCENTAJE DE ACEPTACIÓN EN FUNCIÓN DEL DELTA//
	/*
	for(delta = 0; delta < 50; delta = delta + 0.001)
	{
		
		aceptacion = 0; // reinicio aceptacion
		
		aceptacion = Muestreo(iteraciones, aceptacion, vec, x0, delta); //veo cuantos acepto
		
		porcentaje = (double)aceptacion/(double)iteraciones; //lo escribo como porcentaje
		
		printf("delta = %f\t", delta);
		printf("porcentaje = %f\n", porcentaje);
		
		fprintf(fp,"%f\t", delta);
		fprintf(fp,"%f\n", porcentaje);
		
	}
	*/
	/////////////////////// ACA YA NO //////////////////////////////
	
	//for(delta = 0; delta < 50; delta = delta + 0.001)
	//{
		Muestreo(iteraciones, aceptacion, vec, x0, delta); //veo cuantos acepto		
	//}
	//fclose(fp);
	free(vec);

	return 0;
}