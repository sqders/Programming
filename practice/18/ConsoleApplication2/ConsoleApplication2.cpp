#include <iostream>
#include <string>
using namespace std;

void main()
{
	setlocale(LC_ALL, "ru");
	double alpha[26],value=0,prob=1;
	char symbol;
	string stop;
  const char* aao[] = { "hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen" };
  for (int i = 0; i < 26; i++) {
	  alpha[i] = 0;
  }
	for (int i = 0; i < 6; i++)
	 {
	  for (int j = 0; j < strlen(aao[i]); j++)
	  {
		  for (char w = 97; w < 122; w++)
		  {
			  if (aao[i][j] == w)
				  alpha[w - 97]++;
		  }
	  }
	 }
	for (int i = 0; i < 26; i++)
	{
		value += alpha[i];
	}
	cout << "Введите стоп слово:"<<endl;
	getline(cin, stop);
	for (int j = 0; j<stop.length(); j++)
	{
		for (char w = 97; w < 122; w++)
		{
			if (stop[j] == w)
				prob*=(alpha[w-97]/value);
		}
	}
	cout << prob;
}
