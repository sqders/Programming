#include <iostream>
#include <string>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <locale>
#include <fstream>

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
    svr.Post("/webhooks",Foo_webhooks);
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
    string str=u8R"()",j_str= req.body.c_str();
    

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
        string user_id = to_string(jreq["state"]["application"]["value"].get<int>());

        string users_str = u8"";
        ifstream users_file("users.json");
        string str_p;
        while (!users_file.eof())
        {
            str_p = u8"";
            getline(users_file, str_p);
            users_str += str_p;
        }
        users_file.close();
        json j_users = json::parse(users_str);

        if (j_users["users"][user_id] == jres["nothing"])
        {
            j_users["users"][user_id] = json::object();
            j_users["users"][user_id].push_back({ "tts",1 });
            j_users["users"][user_id]["sina"] = json::object();
            j_users["users"][user_id].push_back({ "mode",1 });
        }

        jres.push_back({ "version","1.0" });
        jres["response"] = json::object();
        jres["response"].push_back({ "text","" });
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
            
        }
        else if (jreq["request"]["command"] == "" && jreq["request"]["original_utterance"] == "ping" && jreq["requset"]["type"] == "SimpleUtterance")
        {

        }
        else if (jreq["request"]["nlu"]["tokens"][0] == u8"молчать")
        {
            jres["response"]["text"] = u8"Молчу, молчу";
            j_users["users"][user_id]["tts"] = 0;
        }
        else if (jreq["request"]["nlu"]["tokens"][0] == u8"молчать")
        {

        }



        if (j_users["users"][user_id]["tts"] == 1)
        {
            string tts = jres["response"]["text"].get<string>();
            jres["response"]["tts"] = tts;
        }
        else
        {
            jres["response"]["buttons"][0]["title"] = u8"Говорить";
            jres["response"]["buttons"][0]["payload"] = u8"Говорить";
        }
            logger << jres;
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
    //logger << req.body.c_str();
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
            logger << j;
    }
    if (req.has_param("set")) {
        ofstream wh_o("wh.json");
        auto val = req.get_param_value("set");
        j["webhooks"].push_back(val);
        wh_o << j;
        wh_o.close();
        logger << j;
    }
    if (j["webhooks"] == NULL)
    {
        res.set_content(webhooks_html, "text/html");
    }
    else
    {
        for (int i = 0; i < j["webhooks"].size(); i++)
        {
            string copy_typ_web = typ_web, url = u8R"(Webhook URL)";
            copy_typ_web = swap(copy_typ_web, url, j["webhooks"][i]);
            copy_typ_web = swap(copy_typ_web, url, j["webhooks"][i]);
            webhooks_html.insert(pos, copy_typ_web);
        }
    }
    
    
    res.set_content(webhooks_html, "text/html; charset=UTF-8");
}