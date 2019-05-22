/* gcc -Wall -O3 -o IS_1A_2.exe ImportanceSamplingEj1A_2.c -lm*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "Muestreo_d.h"
#include "MedVal_d.h"
#include "Normal_d.h"

double Normal(double x0);
double Muestreo(int iteraciones, int aceptacion, double* vec, double x0, double delta);
double mean(double* vec, int iteraciones);
double pseudomean(double* vec, int len_ck, int k);
double mean_xcuad(double* vec, int iteraciones);

int main()
{
	//Variables input
	double x0, delta, *vec, *C_K;
	int iteraciones, aceptacion, len_ck, k ,n, promedios;

	//variables output
	double pseudomed, med_xcuad, medx_cuad, med, result;
		
	printf("\n\ndame un x0\n");
	scanf("%lf",&x0);
	
	printf("Cantidad de x0's que queres\n");
	scanf("%i", &iteraciones);

	//len_ck va a ser (arbitrariamente) el 50% de la longitud de iteraciones.
	len_ck = 50*iteraciones/100;

	vec = (double*)malloc(iteraciones*sizeof(double));
	C_K = (double*)malloc(len_ck*sizeof(double));

	aceptacion = 0;
	promedios = 1000;
	srand(1);
	FILE* fp;
	fp = fopen("CorrelacionVSdelta_a.txt","w");
	
	//me genero un barrido en deltas (fino por demás, facu dijo usar 6 deltas distintos como mucho, pero para probar)
	for(delta = 2; delta < 5; delta = delta + 1)
	{	

		//reinicio el vector C_K
		for(k = 0; k < len_ck; k++)
		{
			C_K[k] = 0;
		}
		
		fprintf(fp,"%lf\t", delta);
		
		for(n = 0; n < promedios; n++)
		{	
			printf("delta = %lf\t",delta);
			printf("n = %i\n", n);
			//corro la función Muestreo para que me arme el vector vec lleno de los x0
			Muestreo(iteraciones, aceptacion, vec, x0, delta);
			
			med = mean(vec, iteraciones);
			med_xcuad = mean_xcuad(vec, iteraciones);
			medx_cuad = med*med;
			
			//reinicio result
			result = 0;
			//voy metiendo en cada coordenada del vector C_K
			for(k = 1; k < len_ck; k ++)
			{
				pseudomed = pseudomean(vec, len_ck, k);
				result = (pseudomed - medx_cuad)/(med_xcuad - medx_cuad);
				C_K[k] += 1.0*result/promedios;
			}
		}
		
		for(k = 1; k < len_ck; k++)
		{
			fprintf(fp,"%lf ", C_K[k]);
		}
		
		fprintf(fp, "\n");
	}
	fclose(fp);
	free(C_K);
	free(vec);
	return 0;
}