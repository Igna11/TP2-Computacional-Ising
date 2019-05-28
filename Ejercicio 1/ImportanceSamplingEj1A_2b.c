/* gcc -Wall -O3 -o IS_1A_2b.exe ImportanceSamplingEj1A_2b.c -lm*/

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
double pseudomean2(double* vec, int len_ck, int k);
double pseudomean_cuad(double* vec, int len_ck, int k);
double mean_xcuad(double* vec, int iteraciones);

int main()
{
	//Variables input
	double x0, delta, *vec, *C_K;
	int iteraciones, aceptacion, len_ck, filas, columnas, k, i;

	//variables output
	double pseudomed, pseudomed2, pseudo2_med, x2_med, x_med2, med, result;
		
	printf("\n\ndame un x0\n");
	scanf("%lf",&x0);
	
	printf("\n\nDame la longitud de cada vector fila\n\n");
	scanf("%i", &columnas);
	
	printf("\n\nDame la cantidad de veces que queres promediar (filas)\n\n");
	scanf("%i", &filas);
		
	//aceptacion no se usa aca pero lo tengo que inicializar igual
	aceptacion = 0;
	
	iteraciones = columnas*filas;
	
	//len_ck es la dimensión del vector donde se apilan los C_K, que tiene que tener longitud N - K, con N = columnas = numero de elementos por fila
	len_ck = columnas/(int)2;
	printf("len_ck = %i\n", len_ck);
	
	vec = (double*)malloc(iteraciones*sizeof(double));
	C_K = (double*)malloc(len_ck*sizeof(double));
	
	srand(time(NULL));
	
	FILE* fp;
	fp = fopen("2705CorrelacionVSDelta_b.txt","w");
	
	//me genero un barrido en deltas (fino por demás, facu dijo usar 6 deltas distintos como mucho, pero para probar)
	for(delta = 2; delta < 10; delta = delta + 2)
	{	
		fprintf(fp,"%lf\t", delta);
		printf("delta = %lf\n", delta);
		//corro la función Muestreo para que me arme el vector vec lleno de los x0
		Muestreo(iteraciones, aceptacion, vec, x0, delta);
				
		//reinicio C_K
		for(k = 0; k < len_ck; k++)
		{
			C_K[k] = 0.0;
		}
		for(i = 0; i < filas; i++)
		{
			/*este for redefine los k-ésimos primeros elementos del vector vec (desde vec[0] hasta vec[columnas]), 
			para que después las funciones mean, pseudomean y mean_xcuad calculen sus cosas usando solo esos elementos 
			(porque no se me ocurrio otra forma para barrer el vector vec de a sectores dentro de las funciones mean, pseudomean etc)
			*/
			printf("va por la fila %i\n",i);
			for(k = 0; k < columnas; k++)
			{	
				vec[k] = vec[i*filas + k];
				//printf("i = %i\t k = %i\n", i,k);

			}
			//printf("vec[] lo arma bien\n");
			
			for(k = 0; k < len_ck; k++)
			{
				//printf("k = %i ", k);
				med = mean(vec, columnas-k);
				
				x2_med = mean_xcuad(vec, columnas - k);
				
				x_med2 = med*med;
				
				pseudomed = pseudomean(vec, columnas - k, k);
				
				pseudomed2 = pseudomean2(vec, columnas - k, k);
				
				pseudo2_med = pseudomean_cuad(vec, columnas -k, k);
				
				result = (pseudomed - med*pseudomed2)/pow((x2_med - x_med2)*(pseudo2_med - pseudomed2*pseudomed2),1/2);
				
				C_K[k] += result/(double)filas;
				
				//if(k == 0)	printf("pseudomed = %lf\t med_cuad =%lf\t result = %lf\t c_k[0] = %lf\n", pseudomed, x2_med, result, C_K[k]);
			}
		}
		
		for(k = 0; k < len_ck; k++)
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