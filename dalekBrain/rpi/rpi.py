from flask import Flask,render_template,Response,request
from camera import CameraFactory
from config import CAMERA_NAME
from motor import cam_motor_obj

app=Flask(__name__)


@app.route("/hello")
def hello_doctor():
    return "HELLO! DOCTOR!"

@app.route("/index")
def index():
    return render_template("index.html")


@app.route("/index/cam-motor",methods=["POST"])
def move_camera():
    move=request.form.get('move')
    cam_motor_obj.move(move)
    return "success"


def gen(camera):
    while True:
        frame = camera.get_frame()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route("/index/stream.mjpg")
def video_stream():

    camera=CameraFactory.create_camera(CAMERA_NAME)
    return Response(gen(camera),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


if __name__=="__main__":
    app.run("0.0.0.0",debug=True)