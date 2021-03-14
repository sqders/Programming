
#include <iostream>

void create(int*& array, int size, int first = 0, int dis = 0) {
    array = new int[size];
    array[0] = first;
    for (int i = 1; i < size; i++)
    {
        array[i] = first + dis * i;
    }
}
void destroy(int*& array) {
    if (array != nullptr)
        delete[] array;
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
    std::cout << "[" << array[0];
    for (int i = 1; i < size; i++)
    {
        std::cout << ", " << array[i];
    }
    std::cout << "]";
    return array;
}
int main() {
    int size, first, dis;
    std::cin >> size >> first >> dis;
    int* link ;
    create( link, size, first, dis);
    sort(link, size);
    print(link, size);
    destroy(link);
}