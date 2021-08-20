from flask import Blueprint, session

datasets = Blueprint('datasets', __name__, static_folder='static', template_folder="templates", )


@datasets.before_request
def restrict_not_autorized():
    if not session.get('logged'):
        return {}, 403


@datasets.route("/")
def base():
    return "Datasets"
