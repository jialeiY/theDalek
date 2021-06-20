import threading
import cv2
from brain.config import *
import time
import os
import functools

class RealBrain(object):

    def __init__(self,eyes,mouth,vision_recognizers=[],rules=[]):
        self.eyes=eyes
        self.mouth=mouth

        self.eye_thread=None
        self.mouth_thread=None

        self.vision_recognizers=vision_recognizers
        self.vision_action_thread=None

        self.vision_output=None
        self.vision_width=480
        self.vision_height=320

        self.rules=rules


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
        self.vision_action_thread.join()

    # def test(self):
    #     for _ in range(5):
    #         # with self.mouth.condition:
    #         #     self.mouth.set_sound(FACE_DETECTED_SOUND)
    #         #     self.mouth.condition.notify_all()
    #         #     print("notified")
    #         frame=self.eyes.get_frame()
    #         print(frame)
    #         time.sleep(4)

    # def get_vision_output(self):
    #     with self.condition:
    #         self.condition.wait()
    #     return self.vision_output
    

    def _vision_recognition_and_play_sound(self):

        process_this_frame = True


        while True:
            frame=self.eyes.get_frame()

            recognized_img=frame
            if process_this_frame:

                recognizer_output_map={}

                for recognizer in self.vision_recognizers:
                    output=recognizer.recognize(frame)

                    recognizer_output_map[recognizer.get_name()]=output


                # with self.condition:

                #     self.vision_output=cv2.imencode(".jpg",output)[1].tobytes()
                #     self.condition.notify_all()
                

                recognized_img=self._build_recognized_img(frame,recognizer_output_map)

                for rule in self.rules:
                    is_hit=functools.reduce(lambda a,b:a and len(recognizer_output_map.get(b,[]))>0,rule["criteria"],True)
                    print(f"rule {rule['name']}: {is_hit}")
                    if is_hit:
                        with self.mouth.condition:
                            self.mouth.set_sound(rule["output"])
                            self.mouth.condition.notify_all()


            output=cv2.cvtColor(recognized_img , cv2.COLOR_RGB2BGR)
                
            process_this_frame=process_this_frame^True

    def _build_recognized_img(self,img,output_map):

            font=cv2.FONT_HERSHEY_SIMPLEX
            for outputs in output_map.values():
                for o in outputs:
                    cv2.rectangle(img, (o.x0,o.y0), (o.x1,o.y1), (0,255,0), 2)
                    cv2.putText(img, o.label, (o.x0+5,o.y0-5), font, 1, (255,255,255), 2)
                    cv2.putText(img, f"{o.score:.2f}", (o.x0+5,o.y0-20), font, 1, (255,255,255), 2)


            if IS_SAVE_OUTPUT and len(outputs)>0:
                cv2.imwrite(os.path.join(VISION_TEST_PATH,f"vision_{int(time.time())}.jpg"), img)

            return img
        