from sys import argv
from cs50 import SQL
import csv

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit()

db = SQL("sqlite:///students.db")

db.execute("DELETE FROM students")

#db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC, PRIMARY KEY(last))")

with open(argv[1], "r") as characters:

    reader = csv.DictReader(characters, delimiter=",")

    for row in reader:
        name = row["name"].split()         #array of size 3 if middle name, or size 2 if no middle name. use len() to differentiate
        house = row["house"]
        birth = row["birth"]

        if len(name) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], name[1], name[2], house, birth)
        elif len(name) == 2:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], (None,), name[1], house, birth)
        else:
            print("Incorrect name size")
            exit()

db.execute("SELECT first, middle, last, house, birth FROM students;")



#db.execute("sql query")
