#include <iostream>
#include <string>

using namespace std;

int main()
{
	int rows,cols=9,g=0;
	cin >> rows;
	int *kol = new int[rows];
	char **mas = new char* [rows];
	
	for (int i = 0; i < rows; i++)
	{
		mas[i] = new char[cols];
	}
		
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cin>>mas[i][j];
		}
	}

	kol[0] = -1;

	for (int i = 0; i < rows; i++)
	{
		if (mas[i][0] == 97 && mas[i][4] == mas[i][5] && mas[i][5] == 53 && mas[i][6] == mas[i][7] && mas[i][6] == 54 && mas[i][8] == 49)
		{
			kol[g] = i;
			g++;
		}
	}
	if (kol[0] == -1)
		cout << -1;
	for (int i = 0; i < g; i++) 
	{
		int h = kol[i];
		for (int j = 0; j < cols; j++)
		{
			cout << mas[h][j];
		}
		cout << ' ';
	}








	for (int i = 0; i < rows; i++)
	{
		delete[] mas[i];
	}
	delete[] mas;
}
