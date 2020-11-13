//ÿ עק
#ifndef aao2
#define aao2
#include "aao.h"
double kol_soch(int k, int n) {
	return fac(n) / (fac(k) * fac(n - k));
}
#endif