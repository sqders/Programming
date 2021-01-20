#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <locale>
#include <fstream>
#include <sstream>
using namespace httplib;
using json = nlohmann::json;
using namespace std;

json j;

string swap(string word, string word_1, string word_2);

void gen_response(const Request& req, Response& res);

void Foo_webhooks(const Request& req, Response& res);



int main() {
   
    ofstream logger("log.txt", ofstream::app);
    Server svr;
    logger << u8"\nserver started\n";
    svr.Post("/", gen_response);
    svr.Post("/webhooks", Foo_webhooks);
    svr.Get("/webhooks", Foo_webhooks);
    svr.listen("localhost", 1234);
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

void gen_response(const Request& req, Response& res) {
    ofstream logger("log.txt", ofstream::app);
    string str = u8R"()", j_str = req.body.c_str();


    if (j_str[0] != '{') {
        string str_p;
        ifstream wh_i("wh.json");
        while (!wh_i.eof())
        {
            str_p = u8"";
            getline(wh_i, str_p);
            str += str_p;
        }
        j = json::parse(str);

    }
    else {
        json jreq = json::parse(req.body.c_str()), jres;






        json j_users;

        jres["version"] = "1.0";
        jres["response"] = json::object();
        jres["response"].push_back({ "text"," " });
        jres["response"].push_back({ "tts","" });
        jres["response"]["buttons"] = json::array();
        jres["response"]["buttons"].push_back(json::object());
        jres["response"]["buttons"][0].push_back({ "title","" });
        jres["response"]["buttons"][0].push_back({ "payload", json::object() });
        jres["response"]["buttons"][0].push_back({ "hide",false });
        jres["response"].push_back({ "end_session",false });
        jres["response"]["buttons"][0]["title"] = u8"Молчать";
        jres["response"]["buttons"][0]["payload"] = u8"Молчать";
        jres["response"]["buttons"].push_back(json::object());
        jres["response"]["buttons"][1]["title"] = u8"Помощь";
        jres["response"]["buttons"][1]["payload"] = u8"Помощь";



        if (jreq["session"]["new"])
        {
            jres["response"]["text"] = u8"Здравствуйте! Я помогу вам с покупками.";
            j_users["tts"] = 1;
            j_users["sina"] = json::array();
            j_users["mode"] = 0;
            jres["user_state_update"] = j_users;
        }
        else
        {
            j_users = jreq["state"]["user"];
       
        if (j_users["mode"] == 1)
        {
            if (jreq["request"]["command"] == "" && jreq["request"]["original_utterance"] == "ping" && jreq["requset"]["type"] == "SimpleUtterance")
            {
                jres["response"]["text"] = u8" ";
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"молчать")
            {
                jres["response"]["text"] = u8"Выключает озвучивание текста\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"говорить")
            {
                jres["response"]["text"] = u8"Включает озвучивание текста\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"помощь")
            {
                jres["response"]["text"] = u8"Помощь помогает вам разобраться в командах навыка\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["payload"] == u8"Выйти из помощи?" || jreq["request"]["command"] == u8"Выйти из помощи?")
            {
                jres["response"]["text"] = u8"Помощь больше не помогает\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["payload"] == u8"Очистить корзину\nО чём ещё рассказать ?")
            {
                jres["response"]["text"] = u8"Убирает все предметы и цены в корзине.Их больше не вернуть...\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"добавить" && jreq["request"]["nlu"]["tokens"][1] == u8"в" && jreq["request"]["nlu"]["tokens"][2] == u8"корзину")
            {
                jres["response"]["text"] = u8"Добавляет в корзину что-то включая цену этого чего-то.\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["payload"] == u8"Что в корзине")
            {
                jres["response"]["text"] = u8"Показывает что находится в корзине и их цену\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"удалить" && jreq["request"]["nlu"]["tokens"][1] == u8"из" && jreq["request"]["nlu"]["tokens"][2] == u8"корзины")
            {
                jres["response"]["text"] = u8"Удаляет что-то из корзины.Что-то будет утрачено навсегда...\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["payload"] == u8"Сумма")
            {
                jres["response"]["text"] = u8"Складывает цены всего что есть в корзине.\nО чём ещё рассказать ?";
            }
            else if (jreq["request"]["payload"] == u8"Выйти из помощи")
            {
                jres["response"]["text"] = u8"Обращайтесь ещё";
                j_users["mode"] = 0;
                jres["user_state_update"] = j_users;
            }
            else if (jreq["request"]["payload"] == u8"Покупка завершена")
            {
                jres["response"]["text"] = u8"Завершает сеанс .До связи\nО чём ещё рассказать ?";
            }
        }
        else {
            if (jreq["request"]["command"] == "" && jreq["request"]["original_utterance"] == "ping" && jreq["requset"]["type"] == "SimpleUtterance")
            {

            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"молчать")
            {
                jres["response"]["text"] = u8"Молчу, молчу";
                j_users["tts"] = 0;
                jres["user_state_update"] = j_users;
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"говорить")
            {
                jres["response"]["text"] = u8"Хорошо";
                j_users["tts"] = 1;
                jres["user_state_update"] = j_users;
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"помощь")
            {
                j_users["mode"] = 1;
                jres["user_state_update"] = j_users;
                jres["response"]["text"] = u8R"(Молчать-мутить навык
Говорить-анмутить навык
Помощь - помогает
Очистить корзину - очищает корзину
Добавить в корзину - добавляет в корзину предмет с ценой
Что в корзине - показывает содержимое корзины
Сумма - складывает цену всех предметов 
О чем рассказать подробнее?)";
                jres["response"]["buttons"][1]["title"] = u8"Выйти из помощи";
                jres["response"]["buttons"][1]["payload"] = u8"Выйти из помощи";

            }
            else if (jreq["request"]["command"] == u8"очистить корзину")
            {
                j_users["sina"] = json::array();
                jres["response"]["text"] = u8"Корзина пуста";
                jres["user_state_update"] = j_users;
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"добавить" && jreq["request"]["nlu"]["tokens"][1] == u8"в" && jreq["request"]["nlu"]["tokens"][2] == u8"корзину")
            {

                string name = u8"", cost = u8"";
                for (int i = 3; i < jreq["request"]["nlu"]["tokens"].size() - 2; i++)
                {
                    name += jreq["request"]["nlu"]["tokens"][i].get<string>() + u8" ";
                }
                int i = jreq["request"]["nlu"]["tokens"].size();
                cost += jreq["request"]["nlu"]["tokens"][i - 2].get<string>() + u8" ";
                cost += jreq["request"]["nlu"]["tokens"][i - 1].get<string>();
                j_users["sina"].push_back(json::object());
                i = j_users["sina"].size();
                j_users["sina"][i - 1].push_back({ "item",name });
                j_users["sina"][i - 1].push_back({ "price",cost });
                jres["response"]["text"] = u8"OK";
                jres["user_state_update"] = j_users;
            }
            else if (jreq["request"]["command"] == u8"что в корзине")
            {
                if (j_users["sina"].size() == 0)
                {
                    jres["response"]["text"] = u8"Корзина пуста";
                }
                else
                {
                    string what_in_the_black_box = u8"";
                    for (int i = 0; i < j_users["sina"].size() - 1; i++)
                    {
                        what_in_the_black_box += j_users["sina"][i]["item"].get<string>() + j_users["sina"][i]["price"].get<string>() + u8'\n';

                    }
                    int  i = j_users["sina"].size() - 1;
                    what_in_the_black_box += j_users["sina"][i]["item"].get<string>() + j_users["sina"][i]["price"].get<string>();
                    jres["response"]["text"] = u8"В корзине :\n" + what_in_the_black_box;
                }
            }
            else if (jreq["request"]["nlu"]["tokens"][0] == u8"удалить" && jreq["request"]["nlu"]["tokens"][1] == u8"из" && jreq["request"]["nlu"]["tokens"][2] == u8"корзины")
            {
                string name = u8"", items = u8"[";
                jres["response"]["text"] = u8"Такого в корзине нет";
                for (int i = 3; i < jreq["request"]["nlu"]["tokens"].size(); i++)
                {
                    name += jreq["request"]["nlu"]["tokens"][i].get<string>() + u8" ";
                }
                int kek = 0;
                for (int i = 0; i < j_users["sina"].size(); i++)
                {
                    if (name == j_users["sina"][i]["item"].get<string>())
                    {
                        jres["response"]["text"] = u8"Удалил " + name;
                        continue;
                    }
                    if (kek != 0)
                    {
                        items += u8",";
                    }
                    kek++;
                    items += u8"{\"item\":\"" + j_users["sina"][i]["item"].get<string>() + u8"\",\"price\":\"" + j_users["sina"][i]["price"].get<string>() + "\"}";

                    logger << items + "\n";
                }
                items += u8"]";
                j_users["sina"] = json::parse(items);
                jres["user_state_update"] = j_users;
            }
            else if (jreq["request"]["command"] == u8"сумма")
            {
                int sum = 0;
                for (int i = 0; i < j_users["sina"].size(); i++)
                {
                    sum += stoi(j_users["sina"][i]["price"].get<string>());
                }
                jres["response"]["text"] = u8"Сумма в корзине составляет " + to_string(sum) + u8" руйблей";
            }
            else if (jreq["request"]["command"] == u8"покупка завершена")
            {
                jres["response"]["end_session"] = true;
                jres["response"]["text"] = u8"Заходите ещё";
                string post_web, plus = "";
                if (jreq["session"]["user"]["user_id"].get<string>() != "") {
                    post_web = "{\"user_id\":\"" + jreq["session"]["user"]["user_id"].get<string>() + "\",\"check\":";
                }
                else
                {
                    post_web = "\"user_id\":\"anonymous\",\"check\":";
                }
                ofstream users_o("users.json");
                users_o << j_users["sina"];
                users_o.close();
                ifstream users_i("users.json");
                while (!users_i.eof())
                {
                    plus = u8"";
                    getline(users_i, plus);
                    post_web += plus;
                }
                post_web += "}";
                users_i.close(); 
                ifstream wh("wh.json");
                string wh_str = "";
                getline(wh, wh_str);
                json webhooks = json::parse(wh_str);
                for (int i = 0; i < webhooks["webhooks"].size(); i++)
                {
                    string webhook = webhooks["webhooks"][i];
                    string str_client_path = "", str_post_path ="";
                    int pos= webhook.find("/",8);
                    if (pos != -1) {
                        str_client_path = webhook.substr(0, pos);
                        str_post_path = webhook.substr(pos);
                    }
                    else { 
                        str_client_path = webhook.substr(0);
                        str_post_path = "/";
                    }
                    const char* client_path = (str_client_path).c_str();
                    const char * post_path = (str_post_path).c_str();
                    
                    Client cli(client_path);
                    auto res = cli.Post(post_path, post_web, "application/json");
                    if (res) {
                        if (res->status == 200) {
                            std::cout << res->body << std::endl;
                        }
                        else {
                            std::cout << "Status code: " << res->status << std::endl;
                        }
                    }
                    else {
                        auto err = res.error();
                        std::cout << "Error code: " << err << std::endl;
                    }
                }
            }
            else{
            jres["response"]["text"] = u8"Введите команду корректно или нажмите на кнопку \"Помощь\" чтобы ознакомится с командами.";
                }
            } 
        }

        if (j_users["tts"] == 1)
        {
            string tts = jres["response"]["text"].get<string>();
            jres["response"]["tts"] = tts;
        }
        else
        {
            jres["response"]["tts"] = "sil <[500]>";
            jres["response"]["buttons"][0]["title"] = u8"Говорить";
            jres["response"]["buttons"][0]["payload"] = u8"Говорить";
        }
        if (j_users["mode"] == 1)
        {
            jres["response"]["buttons"][0]["title"] = u8"Выйти из помощи";
            jres["response"]["buttons"][0]["payload"] = u8"Выйти из помощи";
            jres["response"]["buttons"][1]["title"] = u8"Выйти из помощи?";
            jres["response"]["buttons"][1]["payload"] = u8"Выйти из помощи?";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][2]["title"] = u8"Молчать";
            jres["response"]["buttons"][2]["payload"] = u8"Молчать";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][3]["title"] = u8"Говорить";
            jres["response"]["buttons"][3]["payload"] = u8"Говорить";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][4]["title"] = u8"Помощь";
            jres["response"]["buttons"][4]["payload"] = u8"Помощь";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][5]["title"] = u8"Очистить корзину";
            jres["response"]["buttons"][5]["payload"] = u8"Очистить корзину";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][6]["title"] = u8"Добавить в корзину";
            jres["response"]["buttons"][6]["payload"] = u8"Добавить в корзину";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][7]["title"] = u8"Что в корзине";
            jres["response"]["buttons"][7]["payload"] = u8"Что в корзине";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][8]["title"] = u8"Сумма";
            jres["response"]["buttons"][8]["payload"] = u8"Сумма";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][9]["title"] = u8"Удалить из корзины";
            jres["response"]["buttons"][9]["payload"] = u8"Удалить из корзины";
            jres["response"]["buttons"].push_back(json::object());
            jres["response"]["buttons"][10]["title"] = u8"Покупка завершена";
            jres["response"]["buttons"][10]["payload"] = u8"Покупка завершена";
        }

        string str_p;
        ofstream dio("dio.json");
        dio << jres;
        dio.close();
        ifstream dii("dio.json");
        while (!dii.eof())
        {
            str_p = u8"";
            getline(dii, str_p);
            str += str_p;
        }
        dii.close();

    }


    res.set_content(str, "text/json; charset=UTF-8");
}

void Foo_webhooks(const Request& req, Response& res) {
    ofstream logger("log.txt", ofstream::app);
    ifstream wh_i;
    wh_i.open("wh.json");
    string str = u8R"()", str_p = "";
    while (!wh_i.eof())
    {
        str_p = "";
        getline(wh_i, str_p);
        str += str_p;
    }
    wh_i.close();

    j = json::parse(str);
    std::string webhooks_html = u8"";
    string typ_web = u8R"(<div class="form-row align-items-center">
                    <div class="col">
                      <input type="text" value="Webhook URL" class="form-control mb-2" disabled>
                    </div>
                    
                    <div class="col">
                      <button type="submit" name="del" value="Webhook URL" class="btn btn-danger mb-2">Удалить</button>
                    </div>
                  </div>)";
    string strp;
    ifstream file;
    file.open("include/Webhooks.html");
    while (!file.eof())
    {
        strp = u8"";
        getline(file, strp);
        webhooks_html += strp;
    }
    file.close();
    string stub = u8"{webhooks_list}";
    int pos;
    pos = webhooks_html.find(stub);
    webhooks_html.erase(pos, stub.size());

    if (req.has_param("del")) {
        ofstream wh_o("wh.json");
        auto val = req.get_param_value("del");
        for (int i = 0; i < j["webhooks"].size(); i++)
        {

            if (j["webhooks"][i] == val)
            {
                j["webhooks"].erase(j["webhooks"].begin() + i);
            }

        }
        wh_o << j;
        wh_o.close();
    }
    if (req.has_param("set")) {
        ofstream wh_o("wh.json");
        auto val = req.get_param_value("set");
        j["webhooks"].push_back(val);
        wh_o << j;
        wh_o.close();
    }
        for (int i = 0; i < j["webhooks"].size(); i++)
        {
            string copy_typ_web = typ_web, url = u8R"(Webhook URL)";
            copy_typ_web = swap(copy_typ_web, url, j["webhooks"][i]);
            copy_typ_web = swap(copy_typ_web, url, j["webhooks"][i]);
            webhooks_html.insert(pos, copy_typ_web);
        }
    res.set_content(webhooks_html, "text/html; charset=UTF-8");
}