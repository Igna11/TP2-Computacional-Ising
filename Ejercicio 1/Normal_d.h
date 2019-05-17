#pragma once

double Normal(double x0)
{
	//sin el factor de normalización
	double f = (double)exp(-(((double)pow(x0,2))/2.0));
	return f;
}