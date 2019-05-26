#pragma once
int Flip(int* red, int dim, double B, double T, double J);
double mean(double* vec, int iteraciones);
double pseudomean(double* vec, int len_ck, int k);
double mean_xcuad(double* vec, int iteraciones);

double M_corr(double* mag, double* c_k, int* red, int dim, double B, double T, double J, int muestreos, int k_max)
{
	double M, M_mean, M2_mean, M_mean2, MK_mean, result;
	int i;
	
	for(i = 0; i < muestreos; i++)
	{
		M = Flip(red, dim, B, T, J);
		mag[i] = M;
	}
	//calculo los valores medios:
	M_mean = mean(mag, k_max);
	M2_mean = mean_xcuad(mag, k_max);
	M_mean2 = M_mean*M_mean;
		
	for(i = 0; i < k_max; i++)
	{
		MK_mean = pseudomean(mag, k_max, i);
		result = (MK_mean - M_mean2)/(M2_mean - M_mean2);
		c_k[i] = result;
	}
	return 0;
}