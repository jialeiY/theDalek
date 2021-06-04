from brain.sensors.camera import CameraFactory
from brain.executors.speaker import Speaker
from brain.actions.face_recognition import FaceRecognizer
from brain.config import *
from brain.real_brain import RealBrain

if __name__=="__main__":
    print("start smart brain")
    camera=CameraFactory.create_camera(CAMERA_NAME,width=VISION_WIDTH,height=VISION_HEIGHT)
    speaker=Speaker()

    face_recognizer=FaceRecognizer(FACE_MODEL_PATH,FACE_SCALE,FACE_THR)

    the_brain=RealBrain(eyes=camera,mouth=speaker,vision_recognizers=[face_recognizer])
    the_brain.start()