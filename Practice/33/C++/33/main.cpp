#include <iostream>

using namespace std;
int* create(int size,int first,int d) {
    int* arith = new int[size];
    arith[0]=first;
    arith[1]=0;
    arith[2]=0;
    for (int i =1;i<size;i++)
    {
       arith[i]= first + i*d;
    }
    return arith;
}

int main() {
    int size=4,first=1,d=1;
    int* result = create(size,first,d);
    delete[] result;

}
