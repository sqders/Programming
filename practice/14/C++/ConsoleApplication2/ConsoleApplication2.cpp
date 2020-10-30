#include <iostream>

using namespace std;

int main()
{	
	double x=1, n;
	int t=0;
	cin >> n;
	while (x <= n) {
		t++;
		x *= 2;
	}
	cout << t;
}
