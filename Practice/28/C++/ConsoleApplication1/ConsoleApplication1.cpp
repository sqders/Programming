
#include <iostream>
#include <vector>

using namespace std;

void print_factorization(unsigned int n);

int main()
{
	
	int var;
	cin >> var;
	print_factorization(var);
}
void print_factorization(unsigned int n)
{
	int var = n,first=n,last=0;
	vector<int> slash = {0,0};
	for (int i = 2; i <= var; i++)
		{
			while (var % i == 0)
			{
 				while (slash.size() -1 < i)
				{
				slash.push_back(0);
				}
			slash[i]++;
			var = var / i;
			
			if (first > i && slash[i] != 0&&first==n)
			{
				first = i;
				
			}
			if (last < i && slash[i] != 0)
			{
				last = i;
			}
			}
		}
	for (int i = first; i < slash.size(); i++)
	{	
		
		if (slash[i] == 0)
			continue;
		if (last != i) {
			if (slash[i] == 1)
				cout << i << '*';
			else
			{
				cout << i << '^' << slash[i] << '*';
			}
		}
		else {
			if (slash[i] == 1)
				cout << i ;
			else
			{
				cout << i << '^' << slash[i] ;
			}
		}
	}

}