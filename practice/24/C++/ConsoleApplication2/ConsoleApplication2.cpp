

#include <iostream>
#include <string>
#include <json.hpp>
#include <fstream>
using namespace std;


int main()
{
	string id = "id",complited="true";

	setlocale(LC_ALL, "Russian");
	int mas[200000000];
	string path_of_input = "vhod+vihod+header/in.json";

	ifstream steam;
	steam.open(path_of_input);
	if (!steam.is_open())
	{
		cout << "error file not open"<<"\n";
	}
	else
	{
		cout << "file is open ,all is ok"<<"\n";
		string str;
		while (!steam.eof()) {
			
			getline(steam, str);
			for (int i = 0; i < str.length(); i++)
			{
			
			}
		}
	}


}
