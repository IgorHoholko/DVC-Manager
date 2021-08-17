from flask import Blueprint, render_template

datasets = Blueprint('datasets', __name__, static_folder='static', template_folder="templates", )


@datasets.route("/")
def base():
    return render_template("datasets/projects.html")


@datasets.route("/datasets")
def bb():
    return render_template("datasets/datasets.html")