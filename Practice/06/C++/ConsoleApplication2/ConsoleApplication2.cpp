#include <iostream>
#include<cmath>
using namespace std;
int main()
{
    double a, b, c, x1, x2;
   cin >> a;
   cin >> b;
   cin >> c;
    if (a == 0)
    {
        if (b == 0)
            cout << "Корней нет";
        else
        {
            cout << "x = " << -(c / b);
        }
    }
    if (pow(b, 2) - 4 * a * c > 0)
    {
        cout << "x1 = " << (-b + sqrt(pow(b, 2) - 4 * a * c > 0)) / (2 * a) << endl << "x2 = " << (-b - sqrt(pow(b, 2) - 4 * a * c > 0)) / (2 * a);
    }
    else if (pow(b, 2) - 4 * a * c == 0)
    {
        cout << "x = " << -b / (2 * a);
    }
    else if(pow(b, 2) - 4 * a * c < 0)
        cout<< "Корней нет";

}

