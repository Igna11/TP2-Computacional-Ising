#pragma once

double Normal(double x0);

double Muestreo(int iteraciones, int aceptacion, double* vec, double x0, double delta)
{
	int i;
	double p, x1, fx0, fx1, unif_1, unif_2;
	
	for(i = 0; i < iteraciones; i ++)
	{	
		unif_1 = (double)rand()/(double)RAND_MAX; //un random entre 0 y 1
		unif_2 = (double)rand()/(double)RAND_MAX;
		
		x1 = (double)x0 - (double)delta +(double)2*unif_1*delta; //un random entre x0 - delta y	 x0 + delta
		
		fx0 = Normal(x0);
		fx1 = Normal(x1);
		
		p = fx1/fx0;
		
		if(p > unif_2)
		{
			aceptacion += 1;
			x0 = x1;
		}
		vec[i] = x0;
	}
	return aceptacion;
}