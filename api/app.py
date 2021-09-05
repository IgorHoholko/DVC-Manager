from flask import Flask, jsonify, make_response
import os

from datasets.controllers import datasets
from auth.auth import auth

from extentions import cors, guard, mongo

from lib.models import User


server = Flask(__name__, static_url_path='')

server.config["SECRET_KEY"] = "13221fa2r1wqrasr125"
server.config["MONGO_URI"] = 'mongodb://' + os.environ['MONGODB_USERNAME'] + ':' + os.environ['MONGODB_PASSWORD'] + '@' + os.environ['MONGODB_HOSTNAME'] + ':27017/' + os.environ['MONGODB_DATABASE']

mongo.init_app(server)
cors.init_app(server)
guard.init_app(server, User)


server.register_blueprint(datasets, url_prefix = '/api/datasets')
server.register_blueprint(auth, url_prefix = '/api/auth')



@server.route('/api', methods=["GET"])
def index():
    response = {'name': 'Hi'}
    print('api')
    response = make_response(jsonify(response))
    return response