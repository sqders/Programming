#include <iostream>
int main()
{
	int a, b, c;
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите A и B:";
	std::cin >> a >> b;
	c = a;
	a = b;
	b = c;
	std::cout << "b=" << b << std::endl<< "a=" << a<<"\nобмен обратно без дополнительной переменной\n";
	a = a + b;
	b = a - b;
	a = a - b;
	std::cout << "b=" << b << std::endl << "a=" << a;
	return 0;
}