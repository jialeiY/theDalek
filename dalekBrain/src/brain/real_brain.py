import threading
import cv2
from brain.config import *
import time
import os
import functools
from brain.executors.motor import MotorAction
from brain.actions.object_tracking import CentroidObjectTracker


class RealBrain(object):

    def __init__(self,eyes,mouth,dong,vision_width,vision_height,vision_recognizers=[],rules=[]):
        self.eyes=eyes
        self.mouth=mouth
        self.dong=dong

        self.eye_thread=None
        self.mouth_thread=None
        self.dong_thread=None

        self.vision_recognizers=vision_recognizers
        self.vision_action_thread=None

        self.vision_condition=threading.Condition()
        self.vision_output=None
        self.vision_width=vision_width
        self.vision_height=vision_height

        self.rules=rules

        self.tracker=CentroidObjectTracker()


    def start(self):
        self.eye_thread=threading.Thread(target=self.eyes.start)
        self.eye_thread.start()

        self.mouth_thread=threading.Thread(target=self.mouth.start)
        self.mouth_thread.start()

        self.vision_action_thread=threading.Thread(target=self._vision_recognition_and_play_sound)
        self.vision_action_thread.start()

        self.dong_thread=threading.Thread(target=self.dong.start)
        self.dong_thread.start()

        # thread=threading.Thread(target=self.test)
        # thread.start()

        self.eye_thread.join()
        self.mouth_thread.join()
        self.dong_thread.join()
        self.vision_action_thread.join()

    # def test(self):
    #     for _ in range(5):
    #         with self.dong.condition:
    #             self.dong.set_action(MotorAction.MOVE_FORWARD)
    #             self.dong.condition.notify_all()
    #             print("notified")
            
    #         time.sleep(4)

    def let_us_move(self,action_str):
        with self.dong.condition:
            try:
                action=MotorAction(action_str)
            except Exception as e:
                print(f"not a valid action {action_str}")
                return
            self.dong.set_action(action)
            self.dong.condition.notify_all()
            print(f"move action: {action}")

    def get_vision_output(self):
        # with self.vision_condition:
        #     self.vision_condition.wait()

        return self.vision_output
    

    def _vision_recognition_and_play_sound(self):

        process_this_frame = True


        while True:
    
            img=self.eyes.get_frame()
            recognized_img=img
            if process_this_frame:

                recognizer_output_map={}

                for recognizer in self.vision_recognizers:
                    output=recognizer.recognize(img)
                    if len(output)>0:
                        output=self.tracker.track(output)
                        recognizer_output_map[recognizer.get_name()]=output


                recognized_img=self._build_recognized_img(img,recognizer_output_map)

                for rule in self.rules:
                    is_hit=functools.reduce(lambda a,b:a and len(recognizer_output_map.get(b,[]))>0,rule["criteria"],True)
                    print(f"rule {rule['name']}: {is_hit}")
                    if is_hit:
                        with self.mouth.condition:
                            self.mouth.set_sound(rule["output"])
                            self.mouth.condition.notify_all()


            output=cv2.cvtColor(recognized_img , cv2.COLOR_RGB2BGR)

            with self.vision_condition:
                self.vision_output=output
                self.vision_condition.notify_all()
                
            # process_this_frame=process_this_frame^True

    def _build_recognized_img(self,img,output_map):

            font=cv2.FONT_HERSHEY_SIMPLEX
            for outputs in output_map.values():
                for o in outputs:
                    cv2.rectangle(img, (o.x0,o.y0), (o.x1,o.y1), (0,255,0), 2)
                    cv2.putText(img, o.label, (o.x0+5,o.y0-5), font, 1, (255,255,255), 2)
                    cv2.putText(img, f"{o.score:.2f}", (o.x0+5,o.y0-20), font, 1, (255,255,255), 2)
                    if o.id is not None:
                        cv2.putText(img, f"{o.id}", (int((o.x0+o.x1)/2),int((o.y0+o.y1)/2)), font, 1, (255,255,255), 2)


            if IS_SAVE_OUTPUT and len(output_map)>0:
                cv2.imwrite(os.path.join(VISION_TEST_PATH,f"vision_{int(time.time())}.jpg"), img)

            return img
        