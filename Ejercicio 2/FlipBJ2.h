#pragma once
int Flip(int* red, int dim, double B, double J, double E_suma, double* E) // de ahora en mas, B y J son B* y J*. asi que borré T.
{
	int i, j;
	int suma_primeros, suma_segundos, indice_acop_primeros, indice_acop_segundos, indice_mag;
	int S_arriba, S_abajo, S_izq, S_der, S;
	int S_ab_der, S_ab_izq, S_ar_der, S_ar_izq;
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
			
			S_arriba = red[((j - 1 + dim)%dim)*dim + i];
			S_abajo  = red[((j + 1 + dim)%dim)*dim + i];
			S_izq    = red[j*dim + (i - 1 + dim)%dim];
			S_der    = red[j*dim + (i + 1 + dim)%dim];
			
			S_ar_izq = red[((j - 1 + dim)%dim)*dim + (i - 1 + dim)%dim];
			S_ar_der = red[((j - 1 + dim)%dim)*dim + (i + 1 + dim)%dim];
			S_ab_izq = red[((j + 1 + dim)%dim)*dim + (i - 1 + dim)%dim];
			S_ab_der = red[((j + 1 + dim)%dim)*dim + (i + 1 + dim)%dim];
			
			S = red[j*dim + i];
			
			suma_primeros = S_abajo + S_arriba + S_der + S_izq;
			suma_segundos = S_ar_der + S_ar_izq + S_ab_der + S_ab_izq;
			
			indice_mag = (S + 1)/2;
			indice_acop_primeros = (S*suma_primeros + 4)/2;
			indice_acop_segundos = (-S*suma_segundos + 4)/2; //pongo -S para que ya tenga en cuenta el caso antiferromagnético
			
			P_aceptacion = p_acop[indice_acop_primeros]*p_acop[indice_acop_segundos]*p_mag[indice_mag];

			if(P_aceptacion > rnd) red[j*dim + i] = -S;
			
			E_suma += S*(-J*((S_arriba + S_abajo + S_izq + S_der)/(double)2 -(S_ab_der + S_ab_izq + S_ar_der + S_ar_izq))  -B); //considero energía de segundos vecinos
		}
	}

	E[0] = E_suma/(dim*dim);
	
	for(i = 0; i < dim*dim; i++)
	{
		M += red[i];
	}	
	return M;
}