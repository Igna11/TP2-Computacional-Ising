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
double mean_xcuad(double* vec, int iteraciones);

int main()
{
	//Variables input
	double x0, delta, *vec, *C_K;
	int iteraciones, aceptacion, len_ck, filas, columnas, k , K, i;

	//variables output
	double med, pseudomed, med_xcuad, med_cuadx, result;
		
	printf("\n\ndame un x0\n");
	scanf("%lf",&x0);
	
	printf("Cantidad de x0's que queres\n");
	scanf("%i", &iteraciones);
	
	//aceptacion no se usa aca pero lo tengo que inicializar igual
	aceptacion = 0;
	
	//filas en las que voy a dividir al vector de pasos vec
	//son las subdivisiones a las cuales voy a mirar los c_k y promediar entre ellas
	filas = 20;
	
	//columnas es el tamaño que va a tener cada subparte del vector de los pasos, es decir,
	//si todo fuera una matriz, tendría tantas columnas, o elementos en cada fila.
	//número de elementos por fila.
	columnas = iteraciones/filas;
	
	//K (mayuscula) es el paso máximo entre dos mediciones distintas para ver la correlación entre ellas, dentro de cada fila del vector de pasos
	//K va a ser (arbitrariamente) el 30% de la longitud de cada fila del vector de pasos
	K = 30*columnas/100;
	
	//len_ck es la dimensión del vector donde se apilan los C_K, que tiene que tener longitud N - K, con N = columnas = numero de elementos por fila
	len_ck = columnas - K;
	
	vec = (double*)malloc(iteraciones*sizeof(double));
	C_K = (double*)calloc(len_ck,sizeof(double));
	
	srand(1);
	
	FILE* fp;
	fp = fopen("correlacionvsdeltab.txt","w");
	
	//me genero un barrido en deltas (fino por demás, facu dijo usar 6 deltas distintos como mucho, pero para probar)
	for(delta = 2; delta < 9; delta = delta + 1)
	{	
		fprintf(fp,"%lf\t", delta);
		printf("delta = %lf\n", delta);
		//corro la función Muestreo para que me arme el vector vec lleno de los x0
		Muestreo(iteraciones, aceptacion, vec, x0, delta);
		
		for(i = 0; i < filas; i++)
		{
			/*este for redefine los k-ésimos primeros elementos del vector vec (desde vec[0] hasta vec[columnas]), 
			para que después las funciones mean, pseudomean y mean_xcuad calculen sus cosas usando solo esos elementos 
			(porque no se me ocurrio otra forma para barrer el vector vec de a sectores dentro de las funciones mean, pseudomean etc)
			*/
			for(k = 0; k < columnas; k++)
			{	
				vec[k] = vec[i*columnas + k];
			}	
			
			med = mean(vec, columnas);
			med_xcuad = mean_xcuad(vec, columnas);
			med_cuadx = pow(med_xcuad,2);
			
			for(k = 1; k < len_ck; k++)
			{
				//printf("k = %i", k);
				pseudomed = pseudomean(vec, K, k);
				result = (pseudomed - med)/(med_xcuad - med_cuadx);
				C_K[k] += result/columnas;
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