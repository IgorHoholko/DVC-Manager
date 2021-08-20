from flask import Blueprint, render_template, request, flash, redirect, session

from lib.models.password_manager import User


auth = Blueprint('auth', __name__)



@auth.route('/login', methods=['POST'])
def login():
    if session.get('logged', False):
        ret = {'logged':True}
    else:
        req = request.get_json(force=True)

        username = req.get('username', None)
        password = req.get('password', None)

        user = User(username, password)

        session['logged'] = user.authorized
        session['access_token'] = 'asfasgasg54a6sf54a65s4g'

        ret = {'logged':user.authorized, "access_token": "asfasgasg54a6sf54a65s4g", 'username': username, "role": user.role}
    return ret, 200

  
@auth.route('/refresh', methods=['POST'])
def refresh():
    """
    Refreshes an existing JWT by creating a new one that is a copy of the old
    except that it has a refrehsed access expiration.
    .. example::
       $ curl http://localhost:5000/api/refresh -X GET \
         -H "Authorization: Bearer <your_token>"
    """
    print("refresh request")
    old_token = request.get_data()
    new_token =old_token# guard.refresh_jwt_token(old_token)
    ret = {'access_token': new_token}
    return ret, 200
  

@auth.route('/logout', methods=['POST'])
def logout():
    print("LOGOUT")
    if session.get('logged', False):
        session.pop("logged", None)
        session.pop("loged", None)
    return {}, 200

 