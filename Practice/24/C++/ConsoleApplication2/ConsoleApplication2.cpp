

#include <iostream>
#include <string>
#include "json.hpp"
#include <stdlib.h>
#include <fstream>
using namespace std;

int main()
{
	string id = "\"userId\":", completed = "\"completed\":", True = "true";
	string path_of_input = "in.json", path_of_output="out.json",line;
	ifstream steam;
	int maxid=0;

	steam.open(path_of_input);


	while (!steam.eof())
	{
		getline(steam, line);
		if (line.find(id) == 4)
		{
			int i = line.find(id), end = line.find(',');
			int index = atoi(line.substr(i + id.length(), end - i - id.length()).c_str());
			if (index > maxid)
				maxid = index;
		}
	}

	int* mas=new int[maxid];
	for (int i = 0; i < maxid; i++)
		{
		mas[i] = 0;
		}

	steam.close();
	steam.open(path_of_input);


	if (!steam.is_open())
	{
		cout << "Error file not open.Try put json file in dir with programm.Yes my english is very horosho!"<<"\n";
	}
	else
	{
		//cout << "file is open ,all is ok"<<"\n";
		int index = 0;

		while (!steam.eof()) {
			getline(steam, line);
			if (line.find(id) == 4)
			{
				int i = line.find(id), end = line.find(',');
				index = atoi(line.substr(i + id.length(), end - i - id.length()).c_str());
			}
			if (line.find(completed) == 4 && line.find("true") == 17)
			{
				mas[index - 1]++;
				index = 0;
			}
		}
	}

	ofstream fout;
	fout.open(path_of_output);

	int g = 0;

	fout << "[";
	for (int i = 0; i < maxid; i++)
	{ 
		
		if (mas[i] != 0) {
			if (g) {
			fout << ',';
		}
			fout << '\n';
			fout << "  {\n    \"task_completed\": " << mas[i] << ",\n    \"userId\" : " << i+1 << "\n  }";
			g++;
		}
	}
	fout << "\n]";
	delete[] mas;
		
	
}
