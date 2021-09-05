
from flask_pymongo import PyMongo
import flask_praetorian
import flask_cors

from lib.access.authenticate import authenticate

mongo = PyMongo()
guard = flask_praetorian.Praetorian()
cors = flask_cors.CORS()

guard.authenticate = authenticate