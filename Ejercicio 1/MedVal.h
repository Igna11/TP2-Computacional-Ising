float mean(float* vec, int iteraciones)
{
	float suma = 0;
	float valor_medio = 0;
	int l = 0;
	
	for(l = 0; l < iteraciones; l++)
	{
		suma += vec[l];
	}
	
	valor_medio = (float)suma/(float)iteraciones;

	return valor_medio;
}
float pseudomean(float* vec, int len_ck, int k)
{
	float suma = 0;
	float pseudo_valormedio = 0;
	int l;
	
	for(l = 0; l < len_ck; l++)
	{
		suma += vec[l+k]*vec[l];
	}
	pseudo_valormedio = (float)suma/(float)len_ck;
	
	return pseudo_valormedio;
}

float mean_xcuad(float* vec, int iteraciones)
{
	float suma = 0;
	float valormedio_xcuadrado = 0;
	int l = 0;
	
	for(l = 0; l < iteraciones; l++)
	{
		suma += pow(vec[l],2);
	}
	
	valormedio_xcuadrado = (float)suma/(float)iteraciones;
	
	return valormedio_xcuadrado;
}