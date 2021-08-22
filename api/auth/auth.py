from flask import Blueprint, request, session
import flask_praetorian


from extentions import guard



auth = Blueprint('auth', __name__)



@auth.route('/login', methods=['POST'])
def login():
    """
    Logs a user in by parsing a POST request containing user credentials and
    issuing a JWT token.
    .. example::
       $ curl http://localhost:5000/api/login -X POST \
         -d '{"username":"Yasoob","password":"strongpassword"}'
    """
    req = request.get_json(force=True)
    username = req.get('username', None)
    password = req.get('password', None)
    user = guard.authenticate(username, password)
    ret = {'access_token': guard.encode_jwt_token(user)}
    return ret, 200


@flask_praetorian.auth_required
@auth.route('/refresh', methods=['POST'])
def refresh():
    """
    Refreshes an existing JWT by creating a new one that is a copy of the old
    except that it has a refrehsed access expiration.
    .. example::
       $ curl http://localhost:5000/api/refresh -X POST \
         -d "Authorization: Bearer <your_token>"
    """
    old_token = request.get_data()
    new_token = guard.refresh_jwt_token(old_token)
    ret = {'access_token': new_token}
    return ret, 200
  

@flask_praetorian.auth_required
@auth.route('/logout', methods=['POST'])
def logout():
    """
    Expire an existing JWT.
    .. example::
       $ curl http://localhost:5000/api/logout -X GET \
         -H "Authorization: Bearer <your_token>"
    """
    old_token = request.get_data()
    guard.refresh_jwt_token(old_token, 0)
    return {}, 200


 
@auth.route('/pr')
@flask_praetorian.auth_required
def protected():
    """
    A protected endpoint. The auth_required decorator will require a header
    containing a valid JWT
    .. example::
       $ curl http://localhost:5000/api/protected -X GET \
         -H "Authorization: Bearer <your_token>"
    """
    return {'message': f'protected endpoint (allowed user {flask_praetorian.current_user().username})'}
