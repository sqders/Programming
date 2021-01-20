
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpp_httplib/httplib.h>
#include <locale>
using json = nlohmann::json;
using namespace std;
using namespace httplib;

json weather;

void re_wet()
{
	Client cli_wet("api.openweathermap.org");
	auto wet = cli_wet.Get("/data/2.5/onecall?lat=44.9&lon=34.1&exclude=daily&lang=ru&units=metric&appid=0b187d44dbd22fecded8524e7dcd0a8e");
	weather = json::parse(wet->body);
	ofstream wet_cache("cache.json");
	wet_cache << weather;
	wet_cache.close();
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
int find_nice_time(int current_time)
{
	int nice_time = -1;
	for (int i = 0; i < weather["hourly"].size(); i++) {

		if (current_time < weather["hourly"][i]["dt"])
		{
			nice_time = i;
			break;
		}
		nice_time = -1;
	}
	return nice_time;
}
void raw_response(const Request& req, Response& res) {
	Client time_cli("http://worldtimeapi.org");
	auto time = time_cli.Get("/api/timezone/europe/simferopol");
	json j = json::parse(time->body);
	int current_time = j["unixtime"];
	ifstream wet_caсhe("cache.json");
	string wet_str = "";
	getline(wet_caсhe, wet_str, '\0');
	weather = json::parse(wet_str);
	wet_caсhe.close();
	int nice_time = find_nice_time(current_time);
	if (nice_time == -1)
	{
		re_wet();
		nice_time = find_nice_time(current_time);
	}
	string distr = weather["hourly"][nice_time]["weather"][0]["description"];
	string temp = to_string(int(weather["hourly"][nice_time]["temp"]));
	string str = "{\"pogoda\":\""+distr+"\",\"temp\":"+temp+"}";
	res.set_content(str, "text/json");
}

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
	ifstream wet_caсhe("cache.json");
	string wet_str = "";
	getline(wet_caсhe,wet_str, '\0');
	weather = json::parse(wet_str);
	wet_caсhe.close();
	int nice_time = find_nice_time(current_time);
	if (nice_time == -1)
	{
		re_wet();
		nice_time = find_nice_time(current_time);
	}
	ifstream file;
	file.open(R"(include/Погода сейчас.html)");
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
		
		string distr = weather["hourly"][nice_time]["weather"][0]["description"];
		string temp = to_string(int(weather["hourly"][nice_time]["temp"]));
		string icon = weather["hourly"][nice_time]["weather"][0]["icon"];
		icon += u8"\.png";
			str = swap(str, "{hourly[i].weather[0].description}", distr);
			str = swap(str, "{hourly[i].weather[0].icon}", icon);
		
		str = swap(str, "{hourly[i].temp}", temp);

		res.set_content(str, "text/html");
	}
}

int main() {

	Server svr;
	svr.Get("/", gen_response);
	svr.Get("/raw", raw_response);
	std::cout << "start\n";
	svr.listen("localhost", 3000); 
}