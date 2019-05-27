#pragma once
double mean(double* vec, int iteraciones);
double pseudomean(double* vec, int len_ck, int k);
double mean_xcuad(double* vec, int iteraciones);

double M_corr(double* mag, double* c_k, int k_max)
{
	double M_mean, M2_mean, M_mean2, MK_mean, result;
	int k;

	//calculo los valores medios:
	M_mean = mean(mag, k_max);
	M2_mean = mean_xcuad(mag, k_max);
	M_mean2 = M_mean*M_mean;
		
	for(k = 0; k < k_max; k++)
	{
		MK_mean = pseudomean(mag, k_max, k);
		result = (MK_mean - M_mean2)/(M2_mean - M_mean2);
		c_k[k] = result;
	}
	return 0;
}