
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    vector<int> arr;
    int n,first;
    std::cin >> n;
   

    for (int i = 0; i < n; i++)
    {
        int var;
        cin >> var; 
        if (!arr.empty()) {
            int arr_size = arr.size(), min_pos = -1;
            for (int j = 0; j < arr_size; j++) {
               
                if (arr[j] < var)
                {
                    min_pos = j;
                    break;
                }
            }
            if(min_pos ==-1)
                auto it = arr.insert(arr.end(),1, var);
            else 
                auto it = arr.insert(arr.begin() + min_pos, 1, var);
        }
        else
        {
            arr.push_back(var);
        }
        if(arr.size()>5)
    for (int i = arr.size()-5; i<arr.size(); i++)
    {
        cout << arr[i] << ' ';
    }
        else {
                for (int i = 0; i < arr.size(); i++)
            {
                cout << arr[i] << ' ';
            }
        }
                    
   cout << endl;
    }
    
}
