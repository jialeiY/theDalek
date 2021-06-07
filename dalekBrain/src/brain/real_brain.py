import threading
import cv2
from brain.config import *
import time

class RealBrain(object):

    def __init__(self,eyes,mouth,vision_recognizers=[]):
        self.eyes=eyes
        self.mouth=mouth

        self.eye_thread=None
        self.mouth_thread=None

        self.vision_recognizers=vision_recognizers
        self.vision_action_thread=None

        self.vision_output=None
        self.vision_width=480
        self.vision_height=320


    def start(self):
        self.eye_thread=threading.Thread(target=self.eyes.start)
        self.eye_thread.start()

        
        self.mouth_thread=threading.Thread(target=self.mouth.start)
        self.mouth_thread.start()

        self.vision_action_thread=threading.Thread(target=self._vision_recognition_and_play_sound)
        self.vision_action_thread.start()


        # thread=threading.Thread(target=self.test)
        # thread.start()

        self.eye_thread.join()
        self.mouth_thread.join()

    # def test(self):
    #     for _ in range(5):
    #         with self.mouth.condition:
    #             self.mouth.set_sound(FACE_DETECTED_SOUND)
    #             self.mouth.condition.notify_all()
    #             print("notified")
    #         time.sleep(4)

    # def get_vision_output(self):
    #     with self.condition:
    #         self.condition.wait()
    #     return self.vision_output
    

    def _vision_recognition_and_play_sound(self):

        process_this_frame = True
        is_face_exist=False
        is_dalek_exist=False
        face_recognizer=self.vision_recognizers[0]
        dalek_recognizer=self.vision_recognizers[1]

        while True:
            frame=self.eyes.get_frame()

            recognized_output=frame
            if process_this_frame:
                recognized_output,is_face_exist=face_recognizer.recognize(frame)

                recognized_output,is_dalek_exist=dalek_recognizer.recognize(recognized_output)

            output=cv2.cvtColor(recognized_output , cv2.COLOR_RGB2BGR)
                
            process_this_frame=process_this_frame^True


            # with self.condition:

            #     self.vision_output=cv2.imencode(".jpg",output)[1].tobytes()
            #     self.condition.notify_all()
            print(f"is face exist:{is_face_exist}")
            if is_face_exist:

                with self.mouth.condition:
                    self.mouth.set_sound(FACE_DETECTED_SOUND)
                    self.mouth.condition.notify_all()

            print(f"is dalek exist:{is_dalek_exist}")
            if is_dalek_exist:
                with self.mouth.condition:
                    self.mouth.set_sound(DALEK_DETECTED_SOUND)
                    self.mouth.condition.notify_all()
