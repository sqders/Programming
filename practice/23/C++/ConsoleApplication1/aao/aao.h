//я факториал
#pragma once
int fact = 1;
int oufa = fact;
int fac(int a)
{ 
	if (a == 0)
		return 1;
	fact *= a;
	oufa = fact;
	if (a != 1) return fac(a - 1);
	else {
		fact = 1;
		return oufa;
	}
}