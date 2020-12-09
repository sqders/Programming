#include <typeinfo>	
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

bool sorted(vector<double> arr)
{
    for (int i = 0; i < arr.size()-1; i++)
    {
        if (arr[i] < arr[i + 1])
            continue;
        else
            return 1;
        
   }
    return 0;
}
template<typename T>
vector<double > BozoSort(T args, int n , bool b = 1)
{ 
    
    vector<double > arr ;
    string typ = typeid(T).name();
    if (typ == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >")
    {
        stringstream ss;
        ss << args;
        string var;
        while (ss >> var)
        {
            arr.push_back(atoi(var.c_str()));
        }
    }
  /*  arr;
    if (typ == "class std::vector<double,class std::allocator<double> >")
    {
        T arr = args;
    }*/
    while (sorted(arr))
    {
            int x1 = rand() % n, x2 = rand() % n;
            double term = arr[x1];
            arr[x1] = arr[x2];
            arr[x2] = term;
    }
    if (b)
        return arr;
    else {

        vector<double > new_arr;
        for (int i = arr.size() - 1; i > 0; i--)
        {
            new_arr.push_back(arr[i]);
        }
        return new_arr;
    }
}

int main()
{

    vector<double> arr;
    int n;
    cin >> n;
    string str,zaglush;
    getline(cin, zaglush);
    getline(cin, str);
    stringstream ss;
    ss << str;
    string var;
    while (ss >> var)
    {
        arr.push_back(atoi(var.c_str()));
    }
    vector<double> double_arr=BozoSort(arr,n);
    for (int i = 0; i < n; i++)
    {
        cout << double_arr[i]<<' ';
    }
    cout << endl<< typeid(arr).name();
    /*double_arr = BozoSort(arr, n);
        for (int i = 0; i < n; i++)
        {
            cout << double_arr[i] << ' ';
        }*/
    /*cin >> n;
    getline(cin, zaglush);
    getline(cin, str);*/
}
