/* gcc -Wall -O3 -o Isampling.exe impSampling.c -lm*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include "Muestreo_d.h"
#include "Normal_d.h"

double Normal(double x0);
double Muestreo(int iteraciones, int aceptacion, double* vec, double x0, double delta);

int main()
{
	//Variables input
	double x0, delta, *vec;
	int iteraciones, aceptacion, n;

	printf("\n\ndame un x0\n");
	scanf("%lf",&x0);
	
	printf("Cantidad de x0's que queres\n");
	scanf("%i", &iteraciones);

	vec = (double*)malloc(iteraciones*sizeof(double));

	aceptacion = 0;
	srand(1);
	
	FILE* fp;
	fp = fopen("MuesteroDefinitivo.txt","w");
	
	//me genero un barrido en deltas (fino por demás, facu dijo usar 6 deltas distintos como mucho, pero para probar)
	for(delta = 2; delta < 6; delta = delta + 1)
	{	
		
		printf("delta = %lf\t",delta);
		
		//corro la función Muestreo para que me arme el vector vec lleno de los x0
		Muestreo(iteraciones, aceptacion, vec, x0, delta);
		
		fprintf(fp,"%lf\t", delta);
		for(n = 0; n < iteraciones; n++)
		{
			fprintf(fp,"%lf ", vec[n]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	free(vec);
	return 0;
}