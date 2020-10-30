#include <iostream>
#include <ctime>
#include <string>
using namespace std;

int restart();
int game();

int main()
{
	setlocale(LC_ALL, "ru");
	cout << "Вас приветствует игра УГАДАЙ ЧИСЛО"<<endl;
	return game();
}
int restart() 
{
	cout << "Хотите начать сначала? (1 - ДА )"<<endl;
	char st;
	cin >> st;
	switch (st)
	{
		case 49:
	{
		return game();
		break;
	}
	default:
		return 0;
	}
	
}
int game()
{
	srand(time(NULL));
	int riddle ,win = 0 ,key=-1;
	riddle = rand()%100;
	for (int i = 0; ; i++)
	{
		cin >> key;
		if (key==riddle) 
		{
			cout << "Поздравляю! Вы угадали" << endl;
			break;
		}
		else if (i == 4)
		{
			cout << "Вы проиграли.Было загадано : " << riddle << endl;
			break;
		}
		if (riddle > key)
			cout << "Загаданное число больше" << endl;
		if(riddle<key)
			cout<<"Загаданное число меньше"<<endl;
	}
	return restart();
}