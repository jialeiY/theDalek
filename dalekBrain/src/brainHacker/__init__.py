from flask import Flask


def create_app(brain=None):
    app=Flask(__name__)
    app.config["brain"]=brain

    from brainHacker.hacker import bp
    with app.app_context():
        app.register_blueprint(bp)

    return app


def run_app(app):
    app.run("0.0.0.0",debug=True,use_reloader=False)
