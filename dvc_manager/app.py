from flask import Flask, jsonify, make_response
from flask_login import LoginManager

from datasets.controllers import datasets


from auth.auth import auth


server = Flask(__name__, static_url_path='')

server.config["SECRET_KEY"] = "13221fa2r1wqrasr125"


login_manager = LoginManager(server)

server.register_blueprint(datasets, url_prefix = '/api/datasets')

server.register_blueprint(auth, url_prefix = '/api/auth')


@server.route('/api', methods=["GET"])
def index():
    response = {'name': 'Hi'}
    print('api')
    response = make_response(jsonify(response))
    return response