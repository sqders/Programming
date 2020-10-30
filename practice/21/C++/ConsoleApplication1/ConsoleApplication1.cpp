#include <iostream>
using namespace std;
void printBMI(double BMI);
double BMI(double weight,double height)
{
    return weight/(height*height);
}
void printBMI(double BMI)
{   
  
    if (BMI < 18.5)
        cout << "Underweight";
    if (BMI < 25.0 && BMI >= 18.5)
        cout << "Normal";
    if (BMI >= 25.0 && BMI < 30.0)
        cout << "Overweight";
    if (BMI >= 30.0)
        cout << "Obesity";
    
}
int main()
{
    double wei, hei;
    cin >> wei >> hei;
    hei /= 100;
    printBMI(BMI(wei, hei));
}
