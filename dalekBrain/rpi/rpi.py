from flask import Flask

app=Flask(__name__)

@app.route("/")
def hello_doctor():
    return "HELLO! DOCTOR!"


if __name__=="__main__":
    app.run("0.0.0.0")