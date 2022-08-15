#!/bin/python
# part 1 of a tutorial on user auth with a db
from pathlib import Path
import csv, sqlite3
import sys, time, traceback

USERS_DB = Path("users.db")
USERS_DB_TABLE_NAME = "users"
CSV_FILE = "sample_user_accounts.csv"
db_connection = None; db_cursor = None; db_records = None

def create_table(data):
    # Create table
    init_db()
    db_cursor.execute(f"""CREATE TABLE IF NOT EXISTS {USERS_DB_TABLE_NAME}
                   (id int, username text, password text);""")
    db_cursor.executemany(
        f"insert into {USERS_DB_TABLE_NAME} (id, username, password) VALUES (?, ?, ?);", data)
    db_connection.commit()
    dinit_db()

def get_users():
    global db_records
    init_db()
    db_cursor.execute(f"select * from {USERS_DB_TABLE_NAME};")
    db_records = db_cursor.fetchall()
    print(f"[*] db_records: {db_records}")
    dinit_db()

def get_user(id):
    ret = list(filter((lambda record: record[0] == id),db_records))
    record = None
    if ret:
        record = {"id": ret[-1][0], 
            "username":ret[-1][1],
            "password":ret[-1][2]
        }
    return record

def init_data():
    user_info = []
    with open(CSV_FILE, "r") as fd:
        dr = csv.DictReader(fd)
        user_info = [(i["id"], i["username"], i["password"]) for i in dr]
    print(f"[*] user_info: {user_info}")
    return user_info

def dinit_db():
    try:
        db_connection.close()
    except:
        print(f"[x] {traceback.format_exc()}")

def init_db():
    global db_connection, db_cursor
    try:
        db_connection = sqlite3.connect(USERS_DB)
        db_cursor = db_connection.cursor()
    except:
        print(f"[x] {traceback.format_exc()}")

def main():
    if not USERS_DB.exists() or not USERS_DB.is_file() or len(USERS_DB.read_bytes()) == 0:
        data = init_data()
        print(f"[*] creating table")
        create_table(data)
    get_users()
    try:
        user = get_user(int(sys.argv[1]))
        print(f"[*] user: {user}")
    except:
        print(f"[x] {traceback.format_exc()}")

if __name__ == "__main__":
    main()
