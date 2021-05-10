from modules.camera import CameraFactory
from modules.audio import Audio
from modules.face_recognition import FaceRecognizer
from modules.config import FACE_ENCODING_PATH,CAMERA_NAME
from modules.real_brain import RealBrain

print("init brain")
camera=CameraFactory.create_camera(CAMERA_NAME)
the_audio=Audio()
face_recognizer=FaceRecognizer(FACE_ENCODING_PATH)
the_brain=RealBrain(eyes=camera,mouth=the_audio,face_recognizer=face_recognizer)