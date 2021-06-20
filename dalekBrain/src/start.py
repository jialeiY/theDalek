from brain.sensors.camera import CameraFactory
from brain.executors.speaker import Speaker
from brain.actions.face_recognition import FaceRecognizer
from brain.actions.daleks_recognition import DaleksRecognizer
from brain.config import *
from brain.real_brain import RealBrain
from brainHacker import create_app,run_app

import multiprocessing
from multiprocessing import Process
import threading


if __name__=="__main__":
    print("start smart brain")
    camera=CameraFactory.create_camera(CAMERA_NAME,width=VISION_WIDTH,height=VISION_HEIGHT)
    speaker=Speaker()

    face_recognizer=FaceRecognizer(FACE_MODEL_PATH,FACE_SCALE,FACE_THR)
    dalek_recognizer=DaleksRecognizer(DALEK_MODEL_PATH,DALEK_LABEL_PATH,DALEK_SCALE,DALEK_THR)

    the_brain=RealBrain(eyes=camera,mouth=speaker,vision_recognizers=[face_recognizer,dalek_recognizer],rules=rules)


    hacker_app=create_app(the_brain)
    hacker_p=threading.Thread(target=run_app,args=(hacker_app,))
    
    hacker_p.start()

    the_brain.start()

    hacker_p.join()

