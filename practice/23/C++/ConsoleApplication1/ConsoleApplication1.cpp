//aao - факт 
//aao1 -ряд тейлора
//aao2 - тч
#include <iostream>
#include <iomanip>
#include "aao/aao.h"
#include "aao/aao1.h"
#include "aao/aao2.h"
double pi = 3.141592 ;
int main()
{
    std::cout << "n\tn!" << std::endl;
    for (int i = 1; i < 11; i++)
        std::cout << i << "\t" << fac(i)<<std::endl;
    
    std::cout <<std::endl<< "x" << "\t" << "sin(x)" << std::endl;
    for(double x=0;x<pi/4;x+=pi/180)
            std::cout <<x<<"\t"<<std::setprecision(4)<<teylor(x,5)<<std::endl;
    std::cout << std::endl << "k\tC(k, 10)" << std::endl;
    for (int k = 1; k < 11; k++)
        std::cout << k << "\t" << kol_soch(k, 10)<<std::endl;

    
}
