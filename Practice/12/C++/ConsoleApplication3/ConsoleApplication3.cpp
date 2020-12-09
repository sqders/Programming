#include <iostream>
int fac(int a, int b)
{
	if (a == 0)
		return b;
	b *= a;
	a--;
	return fac(a, b);
}
int main()
{
	int a, b = 1;
	std::cin >> a;
	std::cout << fac(a, b);
}
