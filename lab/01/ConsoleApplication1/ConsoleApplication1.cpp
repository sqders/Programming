
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpp_httplib/httplib.h>
#include <locale>
using json = nlohmann::json;
using namespace std;
using namespace httplib;

//void gen_response(const Request& req, response& result) {
//    client cli("api.openweathermap.org");
//    client time_cli("http://worldtimeapi.org");
//    auto time=time_cli.get("/api/timezone/europe/simferopol");
//    auto res = cli.get("/data/2.5/forecast?id=524901&lat=44.9&lon=34.1&units=metric&exclued=hourly&appid=0b187d44dbd22fecded8524e7dcd0a8e");
//    json j = json::parse(time->body);
//    int current_time = j["unixtime"];
//    json weather = json::parse(res->body);
//    int max_time = 2147483640;
//    for (int i = 0; i < weather["list"].size(); i++)
//    {
//      
//        if (current_time < weather[i]["dt"] && weather[i]["dt"] < max_time)
//        {
//            max_time = weather[i]["dt"];
//        }
//    }
//    cout << max_time;
//    if (res) {
//       
//        if (res->status == 200) {
//            
//          result.set_content(res->body, "text/plain");
//        }
//        else {
//            std::cout << "status code: " << res->status << std::endl;
//        }
//    }
//    else {
//        auto err = res.error();
//        std::cout << "error code: " << err << std::endl;
//    }
//}

int first_in = 0;
json weather;
void re_wet()
{
	Client cli_wet("api.openweathermap.org");
	auto wet = cli_wet.Get("/data/2.5/forecast?id=524901&lat=44.9&lon=34.1&units=metric&exclued=hourly&appid=0b187d44dbd22fecded8524e7dcd0a8e");
	weather = json::parse(wet->body);
}
string swap(string word, string word_1, string word_2)
{
	std::locale::global(std::locale(""));
	size_t pos;
	while ((pos = word.find(word_1)) != std::string::npos)
	{
		word.erase(pos, word_1.size());
		word.insert(pos, word_2);
	}
	return word;
}
//string swap(string inbuf,string search_string, string replace_string)
//{
//	string ou_str = "";
//	
//	while (!inbuf.empty()) {
//		regex re("\\b" + search_string);
//		ou_str=regex_replace(inbuf, re, replace_string, regex_constants::match_any) ;
//		cin.ignore(numeric_limits<streamsize>::max(), '\n');
//	}
//
//	return ou_str;
//
//}	
int nice_time = -1;
void gen_response(const Request& req, Response& res) {

	Client time_cli("http://worldtimeapi.org");
	auto time = time_cli.Get("/api/timezone/europe/simferopol");
	json j = json::parse(time->body);
	int current_time = j["unixtime"];
	if (time) {
		if (time->status == 200) {

		}
		else {
			std::cout << "Status code: " << time->status << std::endl;
			string str = "Status code : " + to_string(time->status);
			res.set_content(str, "text/plain");
		}
	}
	else {
		auto err = time.error();
		std::cout << "Error of time code: " << err << std::endl;
		string str = "Error of time code: " + to_string(err);
		res.set_content(str, "text/plain");
	}

	
	for (int i = 0; i < weather["list"].size(); i++) {

		if (current_time < weather["list"][i]["dt"])
		{
			nice_time = i+1;
			break;
		}
		nice_time = -1;
	}
	if (nice_time == -1)
	{
		re_wet();
		for (int i = 0; i < weather["list"].size(); i++) {
			if (current_time < weather["list"][i]["dt"])
			{
				nice_time = i + 1;
				break;
			}
		}
	}
	cout << j["datetime"] << '<' << weather["list"][nice_time]["dt_txt"];
	ifstream file;
	file.open("include/Погода сейчас.html");
	if (!file.is_open())
	{
		cout << "Ошибка открытия шаблона" << endl;
		res.set_content("Ошибка открытия шаблона", "text/plain");
	}
	
	else {
		
		string str = "", str_p = "";
		while (!file.eof())
		{
			str_p = "";
			getline(file, str_p);
			str += str_p;
		}
		file.close();
		
		string distr = weather["list"][nice_time]["weather"][0]["description"];
		string temp = to_string(int(weather["list"][nice_time]["main"]["temp"]));
		if (distr.find("overcast clouds") == 0)
		{
			cout << "overcast clouds";
			str = swap(str, "{hourly[i].weather[0].description}", "Clouds");
			str = swap(str, "{hourly[i].weather[0].icon}", "overcast_clouds");
			str = swap(str, "{hourly[i].temp}", temp );
		}
		if (distr.find("clear sky") == 0)
		{
			cout << "clear sky";
		}
		if (distr.find("light rain") == 0)
		{
			cout << "light rain";
		}
		if (distr.find("broken clouds") == 0)
		{
			cout << "broken clouds";
		}
		if (distr.find("few clouds") == 0)
		{
			cout << "few clouds";
			str = swap(str, "{hourly[i].weather[0].description}", "Few clouds");
			str = swap(str, "{hourly[i].weather[0].icon}", "broken_clouds1");
			str = swap(str, "{hourly[i].temp}", temp);
		}
		ofstream widget;
		widget.open("widget.txt");
		widget << str;
		widget.close();
		string nice_time_str = to_string(nice_time);
		res.set_content(str, "text/html");

		
	}

	
}

int main() {

	Server svr;                    // Создаём сервер (пока-что не запущен)
	svr.Get("/", gen_response);    // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
	std::cout << "please work please work ueban blyzt na kode rabotai!!\n";
	svr.listen("localhost", 3000); // Запускаем сервер на localhost и порту 1234
}
//int main() {
//	json j2;
//	// Заполняем разными данными
//	j2["num"] = 1;
//	j2["array"] = json::array();
//	j2["array"].push_back(1);
//	j2["array"].push_back(2);
//	j2["object"] = json::object();
//	j2["object"].push_back({ "PI", 3.14 });
//	j2["object"].push_back({ "exp", 2.71 });
//	// Преобразуем в строку и выводим
//	cout << weather.dump(4)<<endl<<j2.dump(4);
//}
