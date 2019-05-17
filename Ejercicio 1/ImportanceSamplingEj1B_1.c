/* gcc -Wall -O3 -o IS_1B_1.exe ImportanceSamplingEj1B_1.c -lm*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "Normal_d.h"

double Normal(double x0);

int main()
{
	double x0, delta, p, x1, fx0, fx1, unif_1, unif_2, *vec;
	int i, iteraciones;
		
	printf("dame un x0\n");
	scanf("%lf",&x0);

	printf("dame un delta\n");
	scanf("%lf",&delta);
	
	printf("dame el numero de iteraciones que queres\n");
	scanf("%i", &iteraciones);
	
	vec = (double*)malloc(iteraciones*sizeof(double));
	
	srand(1);
	
	/*
	EXPORTA LOS X0, ACEPTADOS Y NO ACEPTADOS (PERO NO LOS X1 PROPUESTOS NO ACEPTADOS)
	*/
	
	FILE* fp;
	fp = fopen("IMP-SAMP-x0.txt","w");

	for(i = 0; i < iteraciones; i ++)
	{	
		unif_1 = (double)rand()/(double)RAND_MAX; //un random entre 0 y 1
		unif_2 = (double)rand()/(double)RAND_MAX;
		
		x1 = (double)x0 - (double)delta +(double)2*unif_1*delta; //un random entre x0 - delta y x0 + delta
		
		fx0 = Normal(x0);
		fx1 = Normal(x1);
		
		p = fx1/fx0;
		
		if(p > unif_2)
		{
			x0 = x1;
		}
		fprintf(fp, "%f\t",x0);
		fprintf(fp, "%f\t", fx0);
		fprintf(fp, "%f\n", fx1);
		
	}
	fclose(fp);
	free(vec);
	return 0;
}