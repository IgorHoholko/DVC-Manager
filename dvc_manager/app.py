from genericpath import exists
from flask import Flask, render_template, redirect
import os


from datasets.datasets import datasets
from auth.auth import auth


server = Flask(__name__, static_url_path='')

server.register_blueprint(datasets, url_prefix = '/datasets')

server.register_blueprint(auth, url_prefix = '/auth')

# executor = PipeExecutor('/hostpipe')

@server.route('/')
def root():
    # executor.addGroup("shitgroup")
    # executor.getGroups()
    # executor.getUsers()
    return "Hi"
    return redirect("/datasets"), 302
