#include <iostream>
#include <math.h>
using namespace std;
int main() {
	int o = 0;
	double a=0, b, c;
	setlocale(LC_ALL, "Russian");
	cin >> o;
	switch (o) 
	{
	case (2): 
	{
double k[3][2];
			cin >> k[0][0] >> k[0][1];
			cin >> k[1][0] >> k[1][1];
			cin >> k[2][0] >> k[2][1];
			a = sqrt(pow((k[0][0] - k[1][0]), 2) + pow(k[0][1] - k[1][1], 2));
			b = sqrt(pow((k[1][0] - k[2][0]), 2) + pow(k[1][1] - k[2][1], 2));
			c = sqrt(pow((k[2][0] - k[0][0]), 2) + pow(k[2][1] - k[0][1], 2));
	}
	case(1): {
		if (a == 0) {
			cin >> a >> b >> c;
		}
		double p;
			if ((a + b > c) && (a + c > b) && (c + b > a)) {
				p = (a + b + c) / 2;
				cout << "Площадь треугольника :" << sqrt(p * (p - a) * (p - b) * (p - c));
			}
			else
				cout << "Такого треугольника не существует";
			break;
		}
		return 0;

	}
}
