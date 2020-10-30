#include <iostream>
#include <string>
using namespace std;
int main()
{
	int denga, ass,sum=0,term=0,butilka=-1;
	char a;
	cin >> denga;
	cin >> ass;
	string* name = new string[ass];
	double** sort = new double* [ass];
	double* litr = new double[ass];

	for (int i = 0; i < ass; i++)
		sort[i] = new double[2];
	////////////////////////////////
	for (int i = 0; i < ass; i++) {
		while (1)
		{
			cin.get(a);
			if (a == ' ')
				break;
			name[i] += a;
		}
		cin >> sort[i][0] >> sort[i][1];//0-цена 1-объем
		litr[i] = sort[i][1] / sort[i][0];
	}
	for (int i = 0; i < ass; i++)
	{
		if (denga < sort[i][0])
		{
			cout << -1;

			for (int i = 0; i < ass; i++)
				delete[] sort[i];

			delete[]sort;
			delete[]name;
			delete[]litr;

			return 0;
		}
	}
	for (int i = 1; i < ass; ++i)
	{
		for (int r = 0; r < ass - i; r++)
		{
			if (litr[r] < litr[r + 1])
			{
				string temp4 = name[r];
				int temp1 = litr[r],temp2=sort[r][1],temp3=sort[r][0];
				litr[r] = litr[r + 1];
				litr[r + 1] = temp1;
				sort[r][1] = sort[r + 1][1];
				sort[r + 1][1] = temp2;
				sort[r][0] = sort[r + 1][0];
				sort[r + 1][0] = temp3;
				name[r] = name[r + 1];
				name[r + 1] = temp4;
			}
		}
	}
	while (sum <= denga)
	{	
		term = sum;
		sum += sort[0][0];
		butilka++;
	}
	
	cout << name[0] << ' '<<butilka <<endl<< butilka*sort[0][1] <<endl<< denga - term;


	
	
	
	//////////////////////////
	
	for (int i=0; i < ass; i++)
		delete[] sort[i];
	
	delete[]sort;
	delete[]name;
	delete[]litr;
	
}