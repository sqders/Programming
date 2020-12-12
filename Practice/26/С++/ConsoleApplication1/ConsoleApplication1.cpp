
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;


template <typename T>
bool sorted(vector<T> arr)
{
    for (int i = 0; i < arr.size()-1; i++)
    {
        if (arr[i] < arr[i + 1])
            continue;
        else {

           // cout << "True 1\n";
            return 1;
        }
        
   }

    //cout << "False 1\n";
    return 0;
}
template <typename T>
bool sorted(vector<vector<T>> matrix)
{
    for (int i = 0; i < matrix[0].size(); i++)
    {
        for (int j = 0; j < matrix[0].size() - 1; j++)
        {
            if (matrix[i][j] < matrix[i][j + 1])
            {
                continue;
            }
            else
            {
                return 1;
            }
        }
        if (i < matrix[0].size() - 1) {
            if (matrix[i + 1][0] > matrix[i][matrix[0].size() - 1])
            {
                continue;
            }
            else
            {
                //cout << "true 2\n";
                return 1;
            }
        }
    }

   // cout << "false 2\n";
    return 0;
}

template<typename T>
vector<T> BozoSort(vector<T> arr, bool b = 0)
{ 
    int n = arr.size();
    vector<T> s_arr = arr;
    while (sorted<T>(s_arr))
    {
            int x1 = rand() % n, x2 = rand() % n;
            T term = s_arr[x1];
            s_arr[x1] = s_arr[x2];
            s_arr[x2] = term;
    }
    if (b)
        return s_arr;
    else {

        vector<T> new_arr;
        for (int i = arr.size() - 1; i > -1; i--)
        {
            new_arr.push_back(s_arr[i]);
        }
        return new_arr;
    }
}
//template<typename T>
//vector<double > BozoSort(T arg1, T arg2, T arg3, bool b = 1);

template <typename T>
vector<T> BozoSort(vector<vector<T>> matrix, bool boolbnik=1)
{
    while (sorted<T>(matrix)) {
        int x1 = rand() % matrix.size(), x2 = rand() % matrix.size(), y1 = rand() % matrix.size(), y2 = rand() % matrix.size();
       T temp = matrix[x1][y1];
        matrix[x1][y1] = matrix[x2][y2];
        matrix[x2][y2] = temp;
    }
    vector<T> ret_matrix;
      
        for (int i = 0; i < matrix.size(); i++)
        {

            for (int j = 0; j < matrix.size(); j++)
            {
                ret_matrix.push_back(matrix[i][j]);

            }
        }
    if (boolbnik) {
        
        return ret_matrix;
    }
    else {
        vector<T> new_arr;
        for (int i = ret_matrix.size() - 1; i > -1; i--)
        {
            new_arr.push_back(ret_matrix[i]);
        }
        return new_arr;
    }
}
template <typename T>
vector<T> BozoSort(T a, T b, T c, bool boolbnik=1)
{
    while (!(a < b && b < c))
    {
         T temp;
        int ran = rand() % 4;
        switch (rand() % 4)
        {
        case 0:
            temp = a;
            a = b;
            b = temp;
            break;
        case 1:
            temp = a;
            a = c;
            c = temp;
            break;
        case 2:
            temp = b;
            b = c;
            c = temp;
            break;
        default:
            break;
        }
    }
   
    if (boolbnik)
        return { a,b,c };
    else
        return{ c,b,a };
}


template<typename T>
void rofl()
{
    
    unsigned int n;
    cin >> n;
    vector<T> vec;
    for (unsigned int i = 0; i < n; i++)
    {
        T input;
        cin >> input;
        vec.push_back(input);
    }
    vector<vector<T>> matrix;
    int a = 0;
    for (int i = 0; i < sqrt(n); i++)
    {
        vector<T>temp;
        for (int j = 0; j < sqrt(n); j++)
        {
            temp.push_back(vec[a]);
            a++;
        }
        matrix.push_back(temp);
    }



    vector<T> sorted_vec = BozoSort<T>(vec,true);
    for (int i = 0; i < n; i++)
    {
        cout << sorted_vec[i]<<' ';
    }
    cout << endl;
    sorted_vec = BozoSort<T>(vec,false);
    for (int i = 0; i < n; i++)
    {
        cout << sorted_vec[i] << ' ';
    }
    cout << endl;


    vector<T> sorted_matrix = BozoSort<T>(matrix);
    for (int i = 0; i < n; i++)
    {
        cout << sorted_matrix[i] << ' ';
    }
    cout << endl;
    sorted_matrix = BozoSort<T>(matrix,false);
    for (int i = 0; i < n; i++)
    {
        cout << sorted_matrix[i] << ' ';
    }
   

    vector<T> sorted_abc = BozoSort(vec[0], vec[1], vec[2]);
    for (int i = 0; i < 3; i++)
    {
        cout << sorted_abc[i] << ' ';
    }
    cout << endl;
    sorted_abc = BozoSort(vec[0], vec[1], vec[2],false);
    for (int i = 0; i < 3; i++)
    {
        cout << sorted_abc[i] << ' ';
    }
    cout << endl;
}
int main()
{
    rofl<double>();
    rofl<string>();
}