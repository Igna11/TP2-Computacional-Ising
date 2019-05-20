#pragma once
int flip_aleatorio(int* red, int dim, int pasos, double B, double T)
{
	int r, i;
	double p_updown, p_downup, rnd;
	
	/*si el campo magnético es positivo, la probabilidad de que un spin
	que está alineado con el campo magnético se de vuelta está dada por
	exp(-2*B/T). La probabilidad de que un spin que está apuntando en
	sentido contrario al campo magnético se de vuelta es 1
	*/
	if(B > 0)
	{
		p_updown = exp(-2*B/T);
		p_downup = 1;
	}/*la inversa del caso anterior*/
	
	else
	{
		p_downup = exp(2*B/T);
		p_updown = 1;
	}
	//inicio i
	printf("%lf\n",B);
	i = 0;
	while(i < pasos)
	{
		//r numero aleatorio entero entre 0 y el tamaño de la matriz, para muestrear la matriz de forma aleatoria
		r = dim*dim*rand()/RAND_MAX;
		rnd = (double)rand()/(double)RAND_MAX;
		
		if(red[r] == 1 || p_updown > rnd)
		{
			red[r] = -1;
		}
		if(red[r] == -1 || p_downup > rnd)
		{
			red[r] = 1;
		}
		i++;
	}
	return 0;
}