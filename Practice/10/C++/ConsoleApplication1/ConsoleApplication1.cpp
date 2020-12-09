#include <iostream>
using namespace std;
int main()
{
    int l1, r1, l2, r2, s, s1m, s2m ;
    cin >> s >> l1 >> r1 >> l2 >> r2;
    if ((s < l1 + l2) || (s > r1 + r2))
        cout << -1;
    else 
    {
        s1m = s - r2;
        if (s1m < l1) s1m = l1;
        s2m = s - s1m;
        if (s2m < l2) s2m = l2;
        cout << s1m << ' ' << s2m;
    }
}