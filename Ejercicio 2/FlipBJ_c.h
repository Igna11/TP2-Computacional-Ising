#pragma once
int Flip(int* red, int dim, double B, double J, double E_suma, double* E) // de ahora en mas, B y J son B* y J*. asi que borré T.
{
	int i, j, suma, indice_acop, indice_mag, S_arriba, S_abajo, S_izq, S_der, S;
	double P_aceptacion, rnd, M;
	
	double p_acop[5] = {exp(8*J), exp(4*J), 1, exp(-4*J), exp(-8*J)};
	double p_mag[2] = {exp(2*B), exp(-2*B)};
	
	M = 0.0;
	P_aceptacion = 0.0;
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

			P_aceptacion = p_acop[indice_acop]*p_mag[indice_mag];

			if(P_aceptacion > rnd) red[j*dim + i] = -S;
			
			E_suma += -S*(J*(S_arriba + S_abajo + S_izq + S_der)/(double)2 +B);
		}			
	}
	
	E[0] = E_suma/(dim*dim);

	for(i = 0; i < dim*dim; i++)
	{
		M += red[i];
	}
	return M;
}