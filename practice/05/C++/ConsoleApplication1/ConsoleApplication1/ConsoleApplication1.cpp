#include <iostream>
int main()
{
	setlocale(LC_ALL, "Russian");
	double a = 9.8, x0, v0, t;//лучше использовать тип данных который взаимодействует с точкой
	std::cout << "Введите переменные:";
	std::cin>> x0 >> v0 >> t;
	std::cout << (-1) * v0* t + a * t * t / 2<<std::endl;
	//std::cout << (-1) * v0 *t+ 1 / 2 * a * t * t; такой способ написание выдает неверный ответ так как с точки зрения программирование 1 делиться на 2*a*t*t
	return 0;
}