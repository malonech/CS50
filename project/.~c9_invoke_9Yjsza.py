import os
import sys
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from time import strftime

from helper import apology, login_required

from decimal import getcontext, Decimal
getcontext().prec = 2

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///runner.db")


#homepage
@app.route("/")
@login_required
def index():
    recentruns = db.execute("SELECT Distance, Duration, Pace, Calories, Timestamp FROM rundata WHERE id IS (?) ORDER BY datetime(Timestamp) DESC LIMIT 5", session["user_id"])
    bestpace = db.execute("SELECT Distance, Timestamp, Pace FROM rundata WHERE Pace = (SELECT MIN(Pace) FROM rundata WHERE id IS (?))", session["user_id"])
    longestrun = db.execute("SELECT Distance, Pace, Timestamp FROM rundata WHERE Distance = (SELECT MAX(Distance) FROM rundata WHERE (?) = id)", session["user_id"])

    print(f"{recentruns}")

    """
    PaceDistance=[]
    PacePace=[]
    PaceTimestamp=[]
    RunDistance=[]
    RunPace=[]
    RunTimestamp=[]

    for row in bestpace:
        PaceDistance.append(row["Distance"])
        PacePace.append(row["Pace"])
        PaceTimestamp.append(row["Timestamp"])

    for row in longestrun:
        RunDistance.append(row["Distance"])
        RunPace.append(row["Pace"])
        RunTimestamp.append(row["Timestamp"])
    """
    return render_template("index.html", recentruns = recentruns, bestpace = bestpace, longestrun=longestrun)


@app.route("/entry", methods=["GET", "POST"])
@login_required
def entry():
    if request.method == "GET":
        return render_template("entry.html")
    else:
        distance = (request.form.get("distKm"))
        durationmin = int(request.form.get("minutes"))
        durationsec = int(request.form.get("seconds"))
        now = strftime('%Y-%m-%d %H:%M:%S')

        decimalduration = durationmin + durationsec / 60
        pace = decimalduration / distance

        weight = db.execute("SELECT weight FROM users WHERE id IS (?)", session["user_id"])
        for row in weight:
            userweight = row["weight"]
        calories = round(distance * userweight * 1.036, 1)

        db.execute("INSERT INTO rundata (Distance, Duration, Pace, Calories, Timestamp, id) VALUES (?, ?, ?, ?, ?, ?)", distance, decimalduration, pace, calories, now, session["user_id"])
        return redirect("/history")



@app.route("/history")
@login_required
def history():
    runs = db.execute("SELECT Distance, Duration, Pace, Calories, Timestamp FROM rundata WHERE (?) = id", session["user_id"])
    return render_template("history.html", runs = runs)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/mapper", methods=["GET", "POST"])
@login_required
def mapper():
    if request.method == "GET":
        return render_template("mapper.html")
    else:

        return render_template("mapper.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        weight = request.form.get("weight")

        if (password != confirmation):
            return apology("Passwords do not match", 403)
        else:
            db.execute("INSERT INTO users (username, hash, weight) VALUES (:username, :password, :weight)",
            username=username, password=generate_password_hash(password), weight=weight)

    return redirect("/")


@app.route("/routes", methods=["GET", "POST"])
@login_required
def routes():

    if request.method == "GET":
        owned = db.execute("SELECT Stock, SUM(shares) as shares FROM transactions WHERE id = (?) GROUP BY Stock", session["user_id"])
        return render_template("sell.html", owned=owned)
    else:
        stock = request.form.get("symbol")
        shares = request.form.get("shares")
        ownedshares = db.execute("SELECT SUM(shares) as shares FROM transactions WHERE (?) = Stock AND (?) = id GROUP BY Stock", stock, session["user_id"])
        ownedstock = db.execute("SELECT Stock FROM transactions WHERE (?) = Stock AND (?) = id GROUP BY Stock", stock, session["user_id"])

        print(f"{ownedshares}, {ownedstock}")

        quoted = lookup(stock)
        now = strftime('%Y-%m-%d %H:%M:%S')
        if (lookup(stock) == None):
            return apology("Invalid Stock Symbol")

        for row in ownedshares:
            if (int(shares) > int(row["shares"])):
                return apology("Insufficient quantity of Stocks")

        balancerow = db.execute("SELECT cash FROM users WHERE id IS (?)", session["user_id"])
        for row in balancerow:
            balance = row["cash"]
        print(f"{balance}")

        db.execute("INSERT INTO transactions (Stock, Shares, Price, Total, Timestamp, id) VALUES (?, ?, ?, ?, ?, ?)", stock, int(shares)*(-1), quoted["price"], quoted["price"]*int(shares), now, session["user_id"])
        newbalance = balance + quoted["price"]*int(shares)
        db.execute("UPDATE users SET cash = (?) WHERE id IS (?)", newbalance, session["user_id"])

    return redirect("/entry")

@app.route("/password", methods=["GET", "POST"])
def password():
    if request.method == "GET":
        return render_template("password.html")
    else:
        oldpassword = request.form.get("oldpassword")
        newpassword = request.form.get("newpassword")
        confirmation = request.form.get("confirmation")
        currentpassword = db.execute("SELECT hash from users WHERE (?)=id", session["user_id"])

        print(f"{currentpassword}")
        print(f"{generate_password_hash(oldpassword)}")
        print(f"{check_password_hash(currentpassword, oldpassword)}")

        for row in currentpassword:
            if (check_password_hash(row["hash"], oldpassword) == True):
                if (newpassword == confirmation):
                    db.execute("UPDATE users SET hash = (?) WHERE id IS (?)", generate_password_hash(newpassword), session["user_id"])
                else:
                    return apology("Password and Confirmation do not match")
            else:
                    return apology("Incorrect Current Password")
    return redirect("/")

@app.route("/bodydata", methods=["GET", "POST"])
def bodydata():
    if request.method == "GET":
        currentweight = db.execute("SELECT weight FROM users WHERE id is (?)", session["user_id"])
        return render_template("bodydata.html", currentweight = currentweight)
    else:
        newweight = request.form.get("newweight")
        db.execute("UPDATE users SET weight = (?) WHERE id IS (?)", newweight, session["user_id"])
    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
