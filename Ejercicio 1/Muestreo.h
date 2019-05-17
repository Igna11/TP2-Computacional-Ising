#pragma once

float Normal(float x0);

float Muestreo(int iteraciones, int aceptacion, float*vec, float x0, float delta)
{
	int i;
	float p, x1, fx0, fx1, unif_1, unif_2;
	
	FILE* fp;
	
	fp = fopen("IS_b.txt","w");
		
	srand(1);
	for(i = 0; i < iteraciones; i ++)
	{	
		unif_1 = (float)rand()/(float)RAND_MAX; //un random entre 0 y 1
		unif_2 = (float)rand()/(float)RAND_MAX;
		
		x1 = (float)x0 - (float)delta +(float)2*unif_1*delta; //un random entre x0 - delta y	 x0 + delta
		
		fx0 = Normal(x0);
		fx1 = Normal(x1);
		p = fx1/fx0;
		
		if(p > unif_2)
		{
			aceptacion += 1;
			x0 = x1;
		}	
		//printf("x0 = %f\n", x0);
		fprintf(fp, "%f\n", x0);
		//fprintf(fp, "%f\t", fx0);
		//fprintf(fp, "%f\n", fx1);
	}
	fclose(fp);
	return aceptacion;
}