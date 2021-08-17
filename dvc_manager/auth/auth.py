from flask import Blueprint, render_template, request, flash

from auth.password_manager import PasswordManager

auth = Blueprint('auth', __name__, static_folder='static', template_folder="templates", )

pm = PasswordManager()

@auth.route("/login", methods=["POST", "GET"])
def base():
    if request.method == 'POST':
        print(request.form)
        print(request.form['login'])
        print(request.form['password'])

        print( "LOGED! ", pm.checkAuth(request.form['login'], request.form['password']) )

    return render_template("auth/login.html")