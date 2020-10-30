#include <iostream>
int fun(int a,int b,int v) 
{
	if (b == 1)
		return v;
	v *= a;
	b--;
	return fun(a, b,v);
}

int main()
{	
	int a, b, v;
	std::cin>> a;
	std::cin >> b;
	v = a;
	std::cout << fun(a, b, v);
}
