import os
import sys
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from time import strftime

from helpers import apology, login_required, lookup, usd

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

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    quantities = db.execute("SELECT Stock, SUM(Shares) as qty FROM transactions WHERE id = (?) GROUP BY Stock", session["user_id"])
    userbalance = db.execute("SELECT cash FROM users WHERE id IS (?)", session["user_id"])
    print(f"{userbalance}")
    stock=[]
    qty=[]
    name=[]
    price=[]
    total=[]

    networth = 0

    for row in quantities:
        stock.append(row["Stock"])
        qty.append(row["qty"])
        lookupstock = lookup(row["Stock"])
        name.append(lookupstock["name"])
        price.append(lookupstock["price"])
        total.append(float(row["qty"]) * float(lookupstock["price"]))
        networth = networth + float(row["qty"]) * float(lookupstock["price"])

    for row in userbalance:
        networth = networth + row["cash"]
    print(f"{networth}")
    size = len(stock)
    return render_template("index.html", stock=stock, qty=qty, name=name, price=price, total=total, size=size, balance=userbalance, networth=networth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        stock = request.form.get("symbol")
        shares = request.form.get("shares")
        quoted = lookup(stock)
        now = strftime('%Y-%m-%d %H:%M:%S')
        if (lookup(stock) == None):
            return apology("Invalid Stock Symbol")
        if (int(shares)<1):
            return apology("Invalid quantity")

        balancerow = db.execute("SELECT cash FROM users WHERE id IS (?)", session["user_id"])
        for row in balancerow:
            balance = row["cash"]
        print(f"{balance}")

        if (balance < quoted["price"]*int(shares)):
            return apology("Insufficient funds")

        db.execute("INSERT INTO transactions (Stock, Shares, Price, Total, Timestamp, id) VALUES (?, ?, ?, ?, ?, ?)", stock, int(shares), quoted["price"], quoted["price"]*int(shares), now, session["user_id"])
        newbalance = balance - quoted["price"]*int(shares)
        db.execute("UPDATE users SET cash = (?) WHERE id IS (?)", newbalance, session["user_id"])
        return redirect("/history")



@app.route("/history")
@login_required
def history():
    transactions = db.execute("SELECT Stock, Shares, Price, Total, Timestamp FROM transactions WHERE (?) = id", session["user_id"])
    return render_template("history.html", transactions = transactions)


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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        quote = request.form.get("quote")
        quoted = lookup(quote)

        print(f"{quoted}")

        if (lookup(quote) == None):
            return apology("Invalid Stock Symbol")
        else:
            return render_template("quoted.html", value=quoted)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if (password != confirmation):
            return apology("Passwords do not match", 403)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :password)",
            username=username, password=generate_password_hash(password))

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

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

    return redirect("/history")

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


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
