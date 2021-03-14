// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
int* create(int size,int first=0,int dis=0) {
    int* array = new int[size];
    array[0] = first;
    for (int i = 1; i < size; i++)
    {
        array[i] = first + dis*i;
    }
    return array;
}
void sort(int* array, int size)
{
    int key, j;
    for (int i = 1; i < size; i++) {
        key = array[i];
        j = i;
        while (j > 0 && array[j - 1] > key) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;  
    }
}
int* print(int* array, int size)
{
    cout << "["<<array[0];
    for (int i = 1; i < size; i++)
    {
        cout << ", " << array[i];
    }
    cout << "]";
    return array;
}
int main() {
    int size,first,dis;
    cin >> size >> first >> dis;
    int* result = create(size, first, dis);
    sort(result, size);
    print(result, size);
    delete[] result;
}