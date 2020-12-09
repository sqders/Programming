#include <iostream>
int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	std::cin >> n;
		for(int i = 1; i < n; i++)
		{ 
			if (n % i == 0)
			{
				std::cout << "Составное";
				return 0;
			}
		}
	std::cout << "Простое";
}
