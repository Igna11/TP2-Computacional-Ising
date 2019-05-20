#pragma once
int imprimir(int *red, int dim)
{	
	int i,j;
	//FILE* fp;
	//fp = fopen("gnisi.txt","w");
	for(i = 0; i < dim; i++)
	{
		for(j = 0; j < dim; j++)
		{
			printf("%i ", red[dim*i + j]);
			//fprintf(fp,"%i ", red[dim*i + j]);
		}
		printf("\n");
		//fprintf(fp,"\n");
	}
	printf("\n");
	//fclose(fp);
	
return 0;
}