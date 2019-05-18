/* gcc -Wall -O3 -o IS_1B_2.exe ImportanceSamplingEj1B_2.c -lm*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Normal_d.h"

double Normal(double x0);

int main()
{
	double x0, delta_i, delta_f, d, p, x1, fx0, fx1, unif_1, unif_2, resultado_parcial, resultado_final, *vec;
	int i, iteraciones;
		
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
	EXPORTA LOS X0, ACEPTADOS Y NO ACEPTADOS (PERO NO LOS X1 PROPUESTOS NO ACEPTADOS)
	ESTE SCRIPT ESTUDIA LA CONVERGENCIA AL VALOR REAL DE LA INTEGRAL, EN FUNCIÓN DEL NÚMERO DE ITERACIONES
	LO QUE ES LO MISMO QUE VER EL TIEMPO DE TERMALIZACIÓN.
	
	ENTONCES HAY QUE VER EL TIEMPO DE TERMALIZACIÓN EN FUNCIÓN DE DELTA. 
	*/
	FILE* fp;
	fp = fopen("TtermalizacionVSdelta.txt","w");
	for(d = delta_i; d < delta_f; d = d + 0.5)
	{
		resultado_parcial = 0;
		resultado_final = 0;
		printf("delta = %lf\n", d);
		fprintf(fp, "%lf\t", d);
		for(i = 0; i < iteraciones; i ++)
		{	
			unif_1 = (double)rand()/(double)RAND_MAX; //un random entre 0 y 1
			unif_2 = (double)rand()/(double)RAND_MAX;
			
			x1 = (double)x0 - (double)d +(double)2*unif_1*d; //un random entre x0 - delta y x0 + delta
			
			fx0 = Normal(x0);
			fx1 = Normal(x1);
			
			p = fx1/fx0;
			
			if(p > unif_2)
			{
				x0 = x1;
			}
			
			vec[i] = x0;
			
			resultado_parcial += pow(x0,2.0);
			
			resultado_final = resultado_parcial/(i+1);
			fprintf(fp, "%lf ", resultado_final);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	free(vec);
	return 0;
}