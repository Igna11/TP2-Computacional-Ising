#pragma once
int poblar(int *red, double p, int dim)
{
	int i;
    double r;
	
	for(i = 0; i < dim*dim; i++)
	{
        r = (double)rand()/(double)RAND_MAX;
		//pueblo toda la red con spines down
		red[i] = -1;

		if(r < p)
		{
			//en base a la probabilidad, switcheo algunos spines con probabilidad uniforme
			red[i] = 1;
		}
	}
	return 0;
}