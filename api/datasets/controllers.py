from flask import Blueprint, session
import flask_praetorian

datasets = Blueprint('datasets', __name__, static_folder='static', template_folder="templates", )


# @datasets.before_request
# def restrict_not_autorized():
#     if not session.get('logged'):
#         return {}, 403


@datasets.route("/")
def base():
    return "Datasets"


@datasets.route('/d')
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
