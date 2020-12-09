#include <iostream>
int main()
{
	double a, b;
	char znak;
	std::cin >> a >> znak >> b;
	switch (znak) 
	{
	case(42):
		{
		std::cout << a * b;
		break;
		}
	case(43):
		{
		std::cout << a + b;
		break;
		}
	case(45):
		{
		std::cout << a - b;
		break;
		}
	case(47):
		{
		std::cout << a / b;
		break;
		}
	default:
		{
			std::cout << "fack go back";
			break;
		}
	}
}
