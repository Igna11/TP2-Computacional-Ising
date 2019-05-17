#pragma once
float Normal(float x0)
{
	float f = (1.0/pow(2.0*M_PI,1.0/2.0))*(float)exp(-(((float)pow(x0,2))/2.0));
	return f;
}