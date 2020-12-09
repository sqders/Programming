#include <iostream>
#include <cmath>
#include <string>
using namespace std;
void main()
{
	int l_pass, l_w, g = 0, cow = 0;
	string word, str, l_pass_str, l_w_str, g_str,c_word;
	char gachi;
	cin >> l_pass;
	cin >> word;
	str = "";
	c_word = word;

	l_w = word.length();
	for (int i = 0; i < l_pass; i++)
		str += "0";

	for (int a = 0; a < pow(word.length(), l_pass); a++)
	{
		int sis = a;
		for (int j = 0; j < l_pass; j++)
		{
			int n = sis % l_w;
			str += to_string(n);
			str.erase(0, 1);
			sis /= l_w;
		}
		for (int i = 0; i < l_pass; i++)
		{
			str[i] = word[str[i] - 48];
		}
		for (int i = 0; i < l_pass; i++)
		{
			for (int j = 0; j <= c_word.length(); j++)
			{
				if (str[i] == c_word[j])
				{
					c_word.erase(j, 1);
				}
			}
		}
		if (c_word.length() != 0) {
			c_word = word;
			continue;
		}
			
			cout << str << ' ';
			str.clear();
			c_word = word;
			for (int i = 0; i < l_pass; i++)
				str += "0";
	
	}
}
