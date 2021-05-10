from flask import Flask,render_template,Response,request

from motor import motor_control
from modules import the_brain

app=Flask(__name__)


@app.route("/hello")
def hello_doctor():
    return "HELLO! DOCTOR!"

@app.route("/index")
def index():
    return render_template("index.html",camera={"width":the_brain.vision_width,"height":the_brain.vision_height})


@app.route("/cam-motor",methods=["POST"])
def move_camera():
    direction=request.form.get('move')
    motor_control.move_camera(direction)
    return "success"

@app.route("/car-motor",methods=["POST"])
def move_car():
    direction=request.form.get("move")
    motor_control.move_car(direction)
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


def gen(brain):
    while True:
        frame = brain.get_vision_output()
        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route("/index/stream.mjpg")
def video_stream():

    return Response(gen(the_brain),
                    mimetype='multipart/x-mixed-replace; boundary=frame')


if __name__=="__main__":
    app.run("0.0.0.0",debug=True,use_reloader=False)