#pragma once
int Flip(int* red, int dim, double B, double T, double J);
double mean(double* vec, int iteraciones);
double pseudomean(double* vec, int len_ck, int k);
double mean_xcuad(double* vec, int iteraciones);

double M_corr_pau(double* mag, double* c_k, int* red, int dim, double B, double T, double J, int muestreos, int k_max)
{
	double M, M_mean, M2_mean, M_mean2, MK_mean, result;
	int i;
	
	for(i = 0; i < muestreos; i++)
	{
		M = Flip(red, dim, B, T, J);
		mag[i] = M;
	}
	
	//calculo los valores medios:
		
	for(i = 0; i < k_max; i++)
	{
		M_mean = mean(mag, muestreos-i);
		M2_mean = mean_xcuad(mag, muestreos-i);
		M_mean2 = M_mean*M_mean;
		MK_mean = pseudomean(mag, muestreos-i, i);
		// printf("(<M*M[%i]> - <M>^2) / (<M^2> - <M>^2) = (%.2lf - %.2lf)/(%.2lf - %.2lf)\n",i, MK_mean, M_mean2, M2_mean, M_mean2);
		result = (MK_mean - M_mean2)/(M2_mean - M_mean2);
		c_k[i] = result;
	}
	
	return 0;
}