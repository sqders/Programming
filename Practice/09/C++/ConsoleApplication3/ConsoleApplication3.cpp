#include <iostream>
using namespace std;
int main()
{	
	setlocale(LC_ALL, "Russian");
	int h1, h2, m1, m2;
	char to1, to2;
	cin >> h1 >> to1 >> m1;
	while (to1!=':'||h1<0||h1>23||m1<0||m1>59)
		cin >> h1 >> to1 >> m1;
	cin >> h2 >> to2 >> m2;
	while(to2!=':' || h2 < 0 || h2 > 23 || m2 < 0 || m2 > 59)
		cin >> h1 >> to2 >> m2;
	
	if (abs(h1*60+m1-h2*60-m2)<=15) 
	{
		cout << "Встреча состоится";
	}
	else
	{
		cout << "Встреча не состоится";
	}
}
