#include <iostream>
#include <string>
#include <cmath>

int F(int a) {
	if (a > 1)
		return F(a - 1) * a;
	else
		return 1;
}

void reverse(std::string& str)
{
	for (int i = 0; i < str.length() / 2; i++)
	{
		char tmp = str[i];
		str[i] = str[str.length() - 1 - i];
		str[str.length() - 1 - i] = tmp;
	}
}

std::string sys(int a, std::string str)
{ 
	std::cout << "std::string sys(int a, std::string str)";
	int p = str.length();
	int k = 1;
	std::string res("");
	int counter = 0;;
	while (counter != a)
	{
		res += std::to_string(a % p);
		a /= p;
		std::cout << res<<std::endl;
	}

	reverse(res);
	std::cout << "reverse" << res<<std::endl;
	return res;
}

int charNum_to_int(char a)
{ 
	std::cout << "int charNum_to_int(char a)";
	for (int i = char('0'), j = 0; i < std::numeric_limits<char>::max(); i++, j++)
		if (a == char(i)) {
			std::cout << j << std::endl;
			return j;
		}
}

int main()
{
	int n;
	std::cin >> n;

	std::string k;
	std::cin >> k;

	std::string str("");

	for (int i = 0; i < n; i++)
		str += '0';

	std::string tmp;
	for (int a = 0; a < pow(k.length(), n); a++)
	{
		tmp = sys(a, k);
		for (int j = 0; j < tmp.length(); j++) {
			std::cout << "for (int j = 0; j < tmp.length(); j++)";
			std::cout << str[str.length() - 1 - j] << tmp[tmp.length() - 1 - j]<<std::endl;
			str[str.length() - 1 - j] = tmp[tmp.length() - 1 - j];
			std::cout << str[str.length() - 1 - j] << tmp[tmp.length() - 1 - j] << std::endl;
		}

		for (int j = 0; j < n; j++)
		{
			str[j] = k[charNum_to_int(str[j])];
			std::cout <<"str[j]"<< str[j]<<std::endl;
		}
		std::cout << str << ' ';

		str = "";
		for (int i = 0; i < n; i++)
			str += '0';
	}

	std::cout << '\n';
	return 0;
}