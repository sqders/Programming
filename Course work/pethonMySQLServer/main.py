import pymysql,cryptography
import json
from flask import Flask, request
from config import host, user, password, db_name
import os.path
app = Flask(__name__)
pwd = os.path.abspath(os.path.dirname(__file__))
@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        login_json=json.loads(request.data)
        print(login_json)
        return request.data
    if request.method == 'GET':
        print(request.json)
        return "It`s GET"
@app.route('/login/', methods=['POST'])
def login():
    if request.method== 'POST':
        req_data=json.loads(request.data)
        try:
            connection = pymysql.connect(
                host=host,
                port=3306,
                user=user,
                password=password,
                database=db_name,
                cursorclass=pymysql.cursors.DictCursor
            )
            try:
                with connection.cursor() as cursor:
                    usernames_querry = "SELECT id FROM users WHERE name='%s' AND password='%s' " %\
                                       (req_data["name"],req_data["password"])
                    cursor.execute(usernames_querry)
                    connection.commit()
                    user_id = cursor.fetchall()
                    if len(user_id) !=0:
                        return request.data
                    else:
                        return "dont find login or password"
            finally:
                connection.close()
        except Exception as ex:
            print("connection refused...")
            print(ex)
        return request.data
@app.route('/registr/', methods=['POST'])
def registr():
    if request.method == 'POST':
        req_data = json.loads(request.data)
        try:
            connection = pymysql.connect(
                host=host,
                port=3306,
                user=user,
                password=password,
                database=db_name,
                cursorclass=pymysql.cursors.DictCursor
            )
            try:
                with connection.cursor() as cursor:
                    usernames_querry = "SELECT id FROM users WHERE name='%s' " % req_data["name"]
                    cursor.execute(usernames_querry)
                    connection.commit()
                    user_id = cursor.fetchall()
                    if len(user_id) == 0:
                        add_user_querry = "INSERT INTO `users` (name, password)" \
                                " VALUES ('%s', '%s');" % (req_data["name"],req_data["password"])
                        cursor.execute(add_user_querry)
                        connection.commit()
                    else:
                        return "this username is already exist"
            finally:
                connection.close()
        except Exception as ex:
            print("connection refused...")
            print(ex)
        return request.data

@app.route('/synserver/', methods=['POST'])
def synserver():
    if request.method == 'POST':

        try:
            connection = pymysql.connect(
                host=host,
                port=3306,
                user=user,
                password=password,
                database=db_name,
                cursorclass=pymysql.cursors.DictCursor
            )
            try:
                    req_data = json.loads(request.data)
                    isNewClient = True
                    with connection.cursor() as cursor:
                        usernames_querry = "SELECT DISTINCT`name` FROM `users`"
                        cursor.execute(usernames_querry)
                        connection.commit()
                        usernames = cursor.fetchall()
                        for username in usernames:
                            if username["name"] == req_data["user"]["name"]:
                                isNewClient = False
                    if isNewClient:
                        return "log in or sing up"
                    user_id = 0
                    with connection.cursor() as cursor:
                        user_id_querry = "SELECT DISTINCT`id` FROM `users` WHERE name = '%s'" % req_data["user"]["name"]
                        cursor.execute(user_id_querry)
                        connection.commit()
                        rows = cursor.fetchall()
                        for row in rows:
                            user_id = row['id']
                            print(user_id)
                    with connection.cursor() as cursor:
                        delete_habit_querry = " DELETE FROM `habits` WHERE user_id = '%s' " % user_id
                        cursor.execute(delete_habit_querry)
                        connection.commit()
                        for habit in req_data["habits"]:
                            insert_habit_querry = "INSERT INTO `habits` (count, strike, periodicity, name, time, user_id)" \
                                                  "VALUES (%s, %s, '%s', '%s', '%s', '%s')" \
                                                  % (habit["count"], habit["strike"], habit["periodicity"], habit["name"],
                                                     habit["time"], user_id)
                            cursor.execute(insert_habit_querry)
                            connection.commit()
                    with connection.cursor() as cursor:
                        delete_tags_querry = " DELETE FROM `tags` WHERE user_id = '%s' " % user_id
                        cursor.execute(delete_tags_querry)
                        connection.commit()
                        tags = req_data["tasks"]["tags"]
                        for tag in tags.keys():
                            insert_tag_querry = "INSERT INTO `tags` (tag, red, green, blue, user_id)" \
                                                "VALUES ('%s', %s, %s, %s,'%s')" \
                                                % (tag, tags[tag]["color"]["red"], tags[tag]["color"]["green"],
                                                   tags[tag]["color"]["blue"], user_id)
                            cursor.execute(insert_tag_querry)
                            connection.commit()
                    with connection.cursor() as cursor:
                        delete_task_list_querry = " DELETE FROM `task_list` WHERE user_id = '%s' " % user_id
                        cursor.execute(delete_task_list_querry)
                        connection.commit()
                        task_list = req_data["tasks"]["task_list"]
                        for tag in task_list.keys():
                            for a in range(len(task_list[tag])):
                                insert_task_list_querry = "INSERT INTO `task_list` (user_id, tag, date, task_text)" \
                                                          "VALUES ('%s','%s','%s','%s')" \
                                                          % (user_id, tag, task_list[tag][a]["date"], task_list[tag][a]["text"])
                                cursor.execute(insert_task_list_querry)
                                connection.commit()
                    with connection.cursor() as cursor:
                        delete_tips_querry = " DELETE FROM `tips` WHERE user_id = '%s' " % user_id
                        cursor.execute(delete_tips_querry)
                        connection.commit()
                        req_data["tips"]
                        for tip in req_data["tips"]:
                            insert_tip_querry = "INSERT INTO `tips` (user_id, content, title)" \
                                                "VALUES ('%s','%s','%s')" \
                                                % (user_id, tip["content"], tip["title"])
                            cursor.execute(insert_tip_querry)
                            connection.commit()
            finally:
                 connection.close()
        except Exception as ex:
            print("connection refused...")
            print(ex)
            return("connection to MySQL server refused...")
    return request.data


@app.route('/synclient/', methods=['POST'])
def synclient():
    if request.method == 'POST':
        req_data = json.loads(request.data)
        try:
            connection = pymysql.connect(
                host=host,
                port=3306,
                user=user,
                password=password,
                database=db_name,
                cursorclass=pymysql.cursors.DictCursor
            )
            try:
                user_id=0
                response_json={}
                with connection.cursor() as cursor:
                    usernames_querry = "SELECT id FROM users WHERE name='%s' " % req_data["user"]["name"]
                    cursor.execute(usernames_querry)
                    connection.commit()
                    user_id_response = cursor.fetchall()
                    if len(user_id_response) != 0:
                        user_id=user_id_response[0]["id"]
                    else:
                        return "log in or sign up"
                with connection.cursor() as cursor:
                    tips_select_querry= "SELECT * FROM tips WHERE user_id='%s'" % user_id
                    cursor.execute(tips_select_querry)
                    connection.commit()
                    tips_list = cursor.fetchall()
                    response_json.update({"tips": [] })
                    for tip in tips_list:
                        new_tip={}
                        new_tip.update({"content":tip["content"]})
                        new_tip.update({"title":tip["title"]})
                        response_json["tips"].append(new_tip)
                with connection.cursor() as cursor:
                    tags_select_querry = "SELECT * FROM tags WHERE user_id='%s'" % user_id
                    cursor.execute(tags_select_querry)
                    connection.commit()
                    tags_list = cursor.fetchall()
                    response_json.update({"tasks": {}})
                    response_json["tasks"].update({"tags":{}})
                    for tag in tags_list:
                        color={"red":tag["red"],"blue": tag["blue"],"green": tag["green"]}
                        response_json["tasks"]["tags"].update({tag["tag"]: {}})
                        response_json["tasks"]["tags"][tag["tag"]].update({"color":color})
                with connection.cursor() as cursor:
                    task_list_select_querry = "SELECT * FROM task_list WHERE user_id='%s'" % user_id
                    cursor.execute(task_list_select_querry)
                    connection.commit()
                    task_list = cursor.fetchall()
                    response_json["tasks"].update({"task_list":{}})
                    tags_list=[]
                    for task in task_list:
                        if tags_list.count(task["tag"]) == 0:
                            response_json["tasks"]["task_list"].update({task["tag"]:[]})
                            tags_list.append(task["tag"])
                        new_task = {}
                        new_task["date"] = task["date"]
                        new_task["task_text"] = task["task_text"]
                        response_json["tasks"]["task_list"][task["tag"]].append(new_task)
                with connection.cursor() as cursor:
                    habits_select_querry = "SELECT * FROM habits WHERE user_id='%s'" % user_id
                    cursor.execute(habits_select_querry)
                    connection.commit()
                    habits_list=cursor.fetchall()
                    response_json.update({"habits":[]})
                    for habit in habits_list:
                        new_habit={}
                        new_habit["count"]=habit["count"]
                        new_habit["periodicity"]=habit["periodicity"]
                        new_habit["name"]=habit["name"]
                        new_habit["strike"]=habit["strike"]
                        new_habit["time"]=habit["time"]
                        response_json["habits"].append(new_habit)
                return json.dumps(response_json,indent=0)
            finally:
                connection.close()
        except Exception as ex:
            print("connection refused...")
            print(ex)
        return "Error"

if __name__ == "__main__":
        app.run()


try:
    connection = pymysql.connect(
        host=host,
        port=3306,
        user=user,
        password=password,
        database=db_name,
        cursorclass=pymysql.cursors.DictCursor
    )
    print("successfully connected ...")
    print("#" * 20)

    try:
        with connection.cursor() as cursor:
            create_users_table_query = "CREATE TABLE IF NOT EXISTS `users`(id INT AUTO_INCREMENT," \
                                         " name varchar(32) NOT NULL," \
                                         " password varchar(32) NOT NULL," \
                                         " PRIMARY KEY (id));"
            cursor.execute(create_users_table_query)
            create_habits_table_query = "CREATE TABLE IF NOT EXISTS `habits`(id INT AUTO_INCREMENT," \
                                        " user_id int NOT NULL," \
                                        " count int , " \
                                        " strike INT ," \
                                        " periodicity varchar(64) ," \
                                        " name varchar(64)  ," \
                                        " time  varchar(32) ,PRIMARY KEY (id));"
            cursor.execute(create_habits_table_query)
            create_tags_table_query = "CREATE TABLE IF NOT EXISTS `tags`(id INT AUTO_INCREMENT," \
                                      " user_id int NOT NULL," \
                                      " tag varchar(32) , " \
                                      " red INT ," \
                                      " green INT ," \
                                      " blue INT  ,PRIMARY KEY (id));"
            cursor.execute(create_tags_table_query)
            create_task_list_table_query = "CREATE TABLE IF NOT EXISTS `task_list`(id INT AUTO_INCREMENT," \
                                           " user_id int NOT NULL," \
                                           " tag varchar(32) , " \
                                           " date varchar(32) ," \
                                           " task_text varchar(128) ,PRIMARY KEY (id));"
            cursor.execute(create_task_list_table_query)
            create_tips_table_query = "CREATE TABLE IF NOT EXISTS `tips`(id INT AUTO_INCREMENT," \
                                      " user_id int NOT NULL," \
                                      " content TEXT(65535) , " \
                                      " title varchar(128),PRIMARY KEY (id));"
            cursor.execute(create_tips_table_query)
        isNewClient = True
        with connection.cursor() as cursor:
            usernames_querry = "SELECT DISTINCT`name` FROM `users`"
            cursor.execute(usernames_querry)
            connection.commit()
            usernames = cursor.fetchall()
            for username in usernames:
                if username["name"] == client_username:
                    isNewClient = False
        if isNewClient:
            with connection.cursor() as cursor:
                y = json.dumps(habits)
                insert_new_user_querry = "INSERT INTO `users` (name, password)" \
                                " VALUES ('%s', '%s');" % (client_username, client_password)
                cursor.execute(insert_new_user_querry)
                connection.commit()
        user_id = 0
        with connection.cursor() as cursor:
            user_id_querry = "SELECT DISTINCT`id` FROM `users` WHERE `name` = '%s'" % str(client_username)
            cursor.execute(user_id_querry)
            connection.commit()
            rows = cursor.fetchall()
            for row in rows:
                user_id = row['id']
                print(user_id)
        with connection.cursor() as cursor:
            delete_habit_querry = " DELETE FROM `habits` WHERE user_id = '%s' " % user_id
            cursor.execute(delete_habit_querry)
            connection.commit()
            for habit in main_json["habits"]:
                insert_habit_querry = "INSERT INTO `habits` (count, strike, periodicity, name, time, user_id)"\
                                      "VALUES (%s, %s, '%s', '%s', '%s', '%s')" \
                                      % (habit["count"], habit["strike"], habit["periodicity"], habit["name"], habit["time"], user_id)
                cursor.execute(insert_habit_querry)
                connection.commit()
        with connection.cursor() as cursor:
            delete_tags_querry = " DELETE FROM `tags` WHERE user_id = '%s' " % user_id
            cursor.execute(delete_tags_querry)
            connection.commit()
            tags = main_json["tasks"]["tags"]
            for tag in tags.keys():
                insert_tag_querry = "INSERT INTO `tags` (tag, red, green, blue, user_id)" \
                                    "VALUES ('%s', %s, %s, %s,'%s')" \
                                    % (tag, tags[tag]["color"]["red"], tags[tag]["color"]["green"],
                                       tags[tag]["color"]["blue"], user_id)
                cursor.execute(insert_tag_querry)
                connection.commit()
        with connection.cursor() as cursor:
            delete_task_list_querry = " DELETE FROM `task_list` WHERE user_id = '%s' " % user_id
            cursor.execute(delete_task_list_querry)
            connection.commit()
            task_list = main_json["tasks"]["task_list"]
            for tag in task_list.keys():
                for a in range(len(task_list[tag])):
                    insert_task_list_querry = "INSERT INTO `task_list` (user_id, tag, date, task_text)" \
                                        "VALUES ('%s','%s','%s','%s')" \
                                        % (user_id, tag, task_list[tag][a]["date"], task_list[tag][a]["text"])
                    cursor.execute(insert_task_list_querry)
                    connection.commit()
        with connection.cursor() as cursor:
            delete_tips_querry = " DELETE FROM `tips` WHERE user_id = '%s' " % user_id
            cursor.execute(delete_tips_querry)
            connection.commit()
            main_json["tips"]
            for tip in main_json["tips"]:
                print(tip)
                insert_tip_querry = "INSERT INTO `tips` (user_id, content, title)" \
                                        "VALUES ('%s','%s','%s')" \
                                        % (user_id, tip["content"], tip["title"])
                cursor.execute(insert_tip_querry)
                connection.commit()

    finally:
        connection.close()
except Exception as ex:
    print("connection refused...")
    print(ex)
