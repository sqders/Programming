#include <iostream>
using namespace std;
int kazino[37];
int kaz_var[37];
void restart();
void kazinich(int win)
{
	int max=0,red=0,black=0,kal = 0;

	kaz_var[win]++;

	kal++;

	for (int j = 0; j < 37; j++)
		{
			if (kaz_var[j] > max)
			{
				max = kaz_var[j];
			}
		}
	while (max > 0)
		{
			for (int j = 0; j < 37; j++)
			{
				if (kaz_var[j] == max)
				{
					cout << j<<' ';
				}
			}
			max--;
		}
	cout << endl;

	for (int i = 0; i < 37; i++)
	{
		if (kaz_var[i] != 0)
			continue;
		kazino[i] = i;
	}
	for (int i = 0; i < 37-kal; i++)
	{
		cout << kazino[i] << ' ';

	}
	cout << endl;
	for (int i = 0; i < 37; i++)
	{
		if (i != 0 && (i == 1 || i == 3 || i == 5 || i == 7 || i == 9 || i == 12 || i == 14 || i == 16 || i == 18 || i == 19 || i == 21 || i == 23 || i == 25 || i == 27 || i == 30 || i == 32 || i == 34 || i == 36) && kaz_var > 0)
			red += kaz_var[i];
		else if (i != 0)
			black += kaz_var[i];
	}
	cout << red << ' ' << black<<endl;
	restart();
}
int main()
{
	for (int i = 0; i < 37; i++)
	{
		kazino[i] = i;
	}
	for (int i = 0; i < 37; i++)
	{
		kaz_var[i] = 0;
	}
	restart();
}
void restart()
{
	int win;
	cin >> win;
	if (win < 0)
		return ;
	else
		kazinich(win);
}
