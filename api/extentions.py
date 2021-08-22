

import flask_praetorian
import flask_cors

from lib.access.authenticate import authenticate


guard = flask_praetorian.Praetorian()
cors = flask_cors.CORS()

guard.authenticate = authenticate