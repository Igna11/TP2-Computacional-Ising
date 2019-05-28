#pragma once

double mean(double* vec, int iteraciones)
{
	double suma = 0.0;
	double valor_medio = 0.0;
	int l = 0;
	
	for(l = 0; l < iteraciones; l++)
	{
		suma += vec[l];
	}
	
	valor_medio = (double)suma/(double)iteraciones;

	return valor_medio;
}
double mean_xcuad(double* vec, int iteraciones)
{
	double suma = 0.0;
	double valormedio_xcuadrado = 0.0;
	int l = 0;
	
	for(l = 0; l < iteraciones; l++)
	{
		suma += vec[l]*vec[l];
	}
	
	valormedio_xcuadrado = (double)suma/(double)iteraciones;
	
	return valormedio_xcuadrado;
}

double pseudomean(double* vec, int len_ck, int k)
{
	double suma = 0.0;
	double pseudo_valormedio = 0.0;
	int l;
	
	for(l = 0; l < len_ck; l++)
	{
		suma += vec[l+k]*vec[l];
	}
	pseudo_valormedio = (double)suma/(double)len_ck;
	
	return pseudo_valormedio;
}

double pseudomean2(double* vec, int len_ck, int k)
{
	double suma = 0.0;
	double pseudo_valormedio2 = 0.0;
	int l;
	
	for(l = 0; l < len_ck; l++)
	{
		suma += vec[l+k];
	}
	pseudo_valormedio2 = (double)suma/(double)len_ck;
	
	return pseudo_valormedio2;
}
double pseudomean_cuad(double* vec, int len_ck, int k)
{
	double suma = 0.0;
	double pseudo_valormedio_cuad = 0.0;
	int l;
	
	for(l = 0; l < len_ck; l++)
	{
		suma += vec[l+k]*vec[l+k];
	}
	pseudo_valormedio_cuad = (double)suma/(double)len_ck;
	
	return pseudo_valormedio_cuad;
}
