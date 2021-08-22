from flask import Flask, jsonify, make_response

from datasets.controllers import datasets
from auth.auth import auth

from extentions import cors, guard

from lib.models import User


server = Flask(__name__, static_url_path='')

server.config["SECRET_KEY"] = "13221fa2r1wqrasr125"



server.register_blueprint(datasets, url_prefix = '/api/datasets')

server.register_blueprint(auth, url_prefix = '/api/auth')

cors.init_app(server)

guard.init_app(server, User)

@server.route('/api', methods=["GET"])
def index():
    response = {'name': 'Hi'}
    print('api')
    response = make_response(jsonify(response))
    return response