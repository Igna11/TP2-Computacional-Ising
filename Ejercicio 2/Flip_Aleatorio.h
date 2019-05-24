#pragma once
int flip_aleatorio(int* red, int dim, int muestreos, double B, double T)
{
	int r, i, S, idx;
	double rnd, mag_final;
	
	double p_aceptacion[2] = {exp(2*B/T), exp(-2*B/T)};
	
	for(i = 0; i < muestreos; i++)
	{
		r = (dim*dim-1)*rand()/RAND_MAX;
		rnd = (double)rand()/(double)RAND_MAX;
		
		//me paro en el spin S
		S = red[r];
		
		idx = (S+1)/2;
		
		if(p_aceptacion[idx] > rnd)
		{		
			red[r] = -S;
		}
	}
	
	//calculo la magnetización de la última iteracion (final) como la suma de spines normalizada por la dimension de la red (L^2)
	mag_final = 0.0;
	for(i = 0; i < dim*dim; i++)
	{
		mag_final+= red[i];
	}
	return mag_final;
}