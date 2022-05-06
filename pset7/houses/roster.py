from sys import argv
from cs50 import SQL
import csv

if len(argv) != 2:
    print("Usage: python roster.py 'house'")
    exit()

db = SQL("sqlite:///students.db")

characters = db.execute("SELECT first, middle, last, house, birth FROM students WHERE house = (?) ORDER BY last, first", argv[1])


for row in characters:
    if row['middle'] == None:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")

