import serial
import threading
from enum import Enum


class MotorAction(Enum):
    CAM_UP="cam_up"
    CAM_DOWN="cam_down"

    MOVE_FORWARD="move_forward"
    MOVE_BACKWORD="move_backward"
    MOVE_LEFT="move_left"
    MOVE_RIGHT="move_right"

class MotorControl(object):

    def __init__(self):
        self.serial=serial.Serial("/dev/ttyACM0",9600)
        self._action:MotorAction=None
        self.condition=threading.Condition()
        

    def _send(self,message):
        self.serial.write(message.encode())

    def set_action(self,action:MotorAction):
        self._action=action
    
    def start(self):
        print("start motor")
        while True:
            with self.condition:
                self.condition.wait()
            self.move()
        print("stop motor")
    
    def move(self):
        self._send(self._action.value)
    
