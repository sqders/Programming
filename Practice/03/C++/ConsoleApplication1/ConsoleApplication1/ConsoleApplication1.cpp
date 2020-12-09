#include <iostream>
int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b;
	std::cout << "Введите переменные:";
	std::cin >> a >> b;
	std::cout <<"\n2 типа double\n"<<"Сложение:"<< a + b <<"\nВычитание:"<< a - b <<"\nУмножение:"<< a * b <<"\nДеление:" << a / b << std::endl;
	int int_a, int_b;
	int_a = a;
	int_b = b;
	//int_a и int_b присваивается число до точки из-за этого ответы отчичаются 
	std::cout << "\nПервый int второй double\n" << "Сложение:" << int_a + b << "\nВычитание:" << int_a - b << "\nУмножение:" << int_a * b << "\nДеление:" << int_a / b << std::endl;
	std::cout << "\nПервый double второй int\n" << "Сложение:" << a + int_b << "\nВычитание:" << a - int_b << "\nУмножение:" <<a * int_b << "\nДеление:" << a / int_b << std::endl;
	return 0;
}