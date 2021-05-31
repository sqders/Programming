import pymysql,json
#from flask import Flask,request
from config import host, user, password, db_name

client_username="12"
client_password="13"

habits=[
        {
            "count": 3,
            "name": "",
            "periodicity": "Каждую секунду (тест)",
            "strike": 10,
            "time": "Mon May 31 03:16:28 2021"
        },
        {
            "count": 1,
            "name": "",
            "periodicity": "Каждую секунду (тест)",
            "strike": 5,
            "time": "Mon May 31 03:16:45 2021"
        },
        {
            "count": 1,
            "name": "dota 2 eto kruto cursach eto huevo  @zxcursed",
            "periodicity": "Каждую секунду (тест)",
            "strike": 5,
            "time": "Mon May 31 03:16:52 2021"
        }
    ]
habits_json=json.dumps(habits)


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
            create_table_query = "CREATE TABLE IF NOT EXISTS `users`(id int AUTO_INCREMENT," \
                                        " name varchar(32) NOT NULL," \
                                        " password varchar(32) NOT NULL," \
                                        " habits TEXT COLLATE utf8_unicode_ci," \
                                        " tasks TEXT COLLATE utf8_unicode_ci  ," \
                                        " tips  TEXT COLLATE utf8_unicode_ci  , PRIMARY KEY (id));"
            cursor.execute(create_table_query)
        with connection.cursor() as cursor:
            y = json.dumps(habits)
            insert_querry = "INSERT INTO `users` (name, password)" \
                            " VALUES (%s, %s);" % (client_username,client_password)
            cursor.execute(insert_querry)
            connection.commit()

    finally:
        connection.close()
except Exception as ex:
    print("connection refused...")
    print(ex)
