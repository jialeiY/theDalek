import threading
import cv2
from brain.config import FACE_DETECTED_SOUND
import time

class RealBrain(object):

    def __init__(self,eyes,mouth=None,face_recognizer=None):
        self.eyes=eyes
        self.mouth=mouth

        self.face_recognizer=face_recognizer

        self.vision_output=None
        self.vision_width=480
        self.vision_height=320

        self.eye_thread=None

        # self.condition=threading.Condition()
        # self.thread=threading.Thread(target=self.recognize_face_and_play_sound)
        # self.thread.start()
    
    def start(self):
        self.eye_thread=threading.Thread(target=self.eyes.start)
        self.eye_thread.start()

        # thread=threading.Thread(target=self.test)
        # thread.start()

        self.eye_thread.join()

    # def test(self):
    #     for _ in range(10):
    #         frame=self.eyes.get_frame()
    #         print(frame)
    #         time.sleep(1)

    # def get_vision_output(self):
    #     with self.condition:
    #         self.condition.wait()
    #     return self.vision_output
    

    # def recognize_face_and_play_sound(self):

    #     process_this_frame = True
    #     is_face_exist=False

    #     while True:
    #         frame=self.eyes.get_frame()

    #         recognized_output=frame
    #         if process_this_frame:
    #             recognized_output,is_face_exist=self.face_recognizer.recognize(frame)

    #         output=cv2.cvtColor(recognized_output , cv2.COLOR_RGB2BGR)
                
    #         process_this_frame=process_this_frame^True


    #         with self.condition:

    #             self.vision_output=cv2.imencode(".jpg",output)[1].tobytes()
    #             self.condition.notify_all()

    #         with self.mouth.condition:
    #             self.mouth.sound=FACE_DETECTED_SOUND if is_face_exist else None
    #             self.mouth.condition.notify_all()



        # print("init camera")
        # if BaseCamera.thread is None:
        #     BaseCamera.last_access=time.time()

        #     BaseCamera.condition=threading.Condition()
        #     BaseCamera.thread=threading.Thread(target=self._thread)
        #     BaseCamera.thread.start()
        #     print("init camera thread")

        #     while self.get_frame() is None:
        #         time.sleep(0)
