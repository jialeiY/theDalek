from flask import Flask,render_template,Response,request,current_app,Blueprint
import cv2
import numpy as np

from os.path import join ,dirname,abspath
bp=Blueprint("bp",__name__)

@bp.route("/hello")
def hello_doctor():
    return "HELLO! DOCTOR!"

@bp.route("/index")
def index():
    brain=current_app.config["brain"]
    return render_template("index.html",camera={"width":brain.vision_width,"height":brain.vision_height})


def gen(brain):
    while True:
        img = brain.get_vision_output()
        if img is None:
            img=np.zeros([512,512,3],dtype=np.uint8)

        frame=cv2.imencode(".jpg",img)[1].tobytes()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@bp.route("/index/stream.mjpg")
def video_stream():
    brain=current_app.config["brain"]
    return Response(gen(brain),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


@bp.route("/cam-motor",methods=["POST"])
def move_camera():
    direction=request.form.get('move')
    brain=current_app.config["brain"]
    brain.let_us_move(direction)
    return "success"

@bp.route("/car-motor",methods=["POST"])
def move_car():
    direction=request.form.get("move")
    brain=current_app.config["brain"]
    brain.let_us_move(direction)
    return "success"

# @app.route("/faces",methods=["POST"])
# def add_face():
#     face_name=request.form.get("face_name")
#     print(f"face name is: {face_name}")

#     status="success"
#     try:
#         camera=CameraFactory.create_camera()
#         faceRecognizerTrainer=FaceRecognizerTrainer(camera,FACE_ENCODING_PATH)
#         faceRecognizerTrainer.add_face(face_name)
#         camera.face_recognizer.load_face_encodings()

#     except Exception as e:
#         status="failed"

#     return status

