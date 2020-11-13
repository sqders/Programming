//ÿ נÿה עויכמנא
#ifndef aao1
#define aao1
#include <cmath>
#include "aao.h"
double teylor(double x, int k)
{
	double teylor_out = 0,teylor_sum=0;
	for(double i = 0 ;i<=k;i++)
	{
		teylor_sum += (pow(-1,i)*pow(x,2*i+1))/fac(2*i+1);	
	}
	teylor_out = teylor_sum;
	teylor_sum = 0;
	return teylor_out;
}

#endif