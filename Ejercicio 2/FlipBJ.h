#pragma once
int Flip(int* red, int dim, int muestreos, double B, double T, double J)
{
	int i, j, k, suma, indice_acop, indice_mag, S_arriba, S_abajo, S_izq, S_der, S;
	double P_aceptacion, rnd;
	
	double p_acop[5] = {exp(8*J/T), exp(4*J/T), 1, exp(-4*J/T), exp(-8*J/T)};
	double p_mag[2] = {exp(2*B/T), exp(-2*B/T)};
	 
	P_aceptacion = 0.0;
	for(k = 0; k < muestreos; k++)
	{
		for(j = 0; j < dim; j++)
		{
			for(i = 0; i < dim; i++)
			{
				//el numero random entre 0 y 1
				rnd = (double)rand()/(double)RAND_MAX;
				
				//chequeado 23-05-2019 y funciona!
				S_arriba = red[((j - 1 + dim)%dim)*dim + i];
				S_abajo  = red[((j + 1 + dim)%dim)*dim + i];
				S_izq    = red[j*dim + (i - 1 + dim)%dim];
				S_der    = red[j*dim + (i + 1 + dim)%dim];
				
				S = red[j*dim + i];
				
				suma = S_abajo + S_arriba + S_der + S_izq;
				
				indice_mag = (S + 1)/2;
				indice_acop = (S*suma + 4)/2;
				printf("S_1 = %i\t",red[j*dim + i]);
				P_aceptacion = p_acop[indice_acop]*p_mag[indice_mag];
				if(P_aceptacion > rnd) red[j*dim + i] = -S;
				printf("S_2 = %i, elemento = %i\t p_acept = %lf\t rand =%lf\n", red[j*dim + i], j*dim + i, P_aceptacion, rnd);
				/*
				printf("\t%i\n", S_arriba);
				printf("%i\t%i\t%i\n", S_izq, S, S_der);
				printf("\t%i\n\n", S_abajo);
				*/
				/*
				if(S*suma == 4) printf("suma = %i, es p acoplamiento = %lf, p mag = %lf\n",suma, p_acop[0], p_mag[1]);
				if(S*suma == 2) printf("suma = %i, es p acoplamiento = %lf, p mag = %lf\n",suma, p_acop[1], p_mag[1]);
				if(S*suma == 0) printf("suma = %i, es p acoplamiento = %lf, p mag = %lf\n",suma, p_acop[2], p_mag[1]);
				if(S*suma == -2) printf("suma = %i, es p acoplamiento = %lf, p mag = %lf\n",suma, p_acop[3], p_mag[1]);
				if(S*suma == -4) printf("suma = %i, es p acoplamiento = %lf, p mag = %lf\n",suma, p_acop[4], p_mag[1]);			
				*/
			}			
		}
	}
	return 0;
}