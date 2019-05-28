#pragma once
double mean(double* vec, int iteraciones);
double pseudomean(double* vec, int len_ck, int k);
double mean_xcuad(double* vec, int iteraciones);

double M_corr(double* mag, double* c_k, int muestreos, int k)
{
	double M_mean, M2_mean, M_mean2, MK_mean, result;
	int k, K;
	
	K = muestreos - k
	
	//calculo los valores medios:
	M_mean = mean(mag, K);
	M2_mean = mean_xcuad(mag, K);
	M_mean2 = M_mean*M_mean;
	
	Mk_mean = 
	Mk2_mean = 
	Mk_mean2 = 
	MK_mean = pseudomean(mag, k_max, k);
	result = (MK_mean - M_mean2)/(M2_mean - M_mean2);

	return result;
}