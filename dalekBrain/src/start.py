from brain.sensors.camera import CameraFactory
from brain.executors.speaker import Speaker
from brain.actions.face_recognition import FaceRecognizer
from brain.config import FACE_ENCODING_PATH,CAMERA_NAME,VISION_WIDTH,VISION_HEIGHT
from brain.real_brain import RealBrain

if __name__=="__main__":
    print("start smart brain")
    camera=CameraFactory.create_camera(CAMERA_NAME,width=VISION_WIDTH,height=VISION_HEIGHT)
    speaker=Speaker()
    # face_recognizer=FaceRecognizer(FACE_ENCODING_PATH)
    the_brain=RealBrain(eyes=camera,mouth=speaker)
    the_brain.start()