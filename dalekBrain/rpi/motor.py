import serial

class MotorControl(object):

    def __init__(self):
        self.serial=serial.Serial("/dev/ttyACM0",9600)

    def __send(self,message):
        self.serial.write(message.encode())
    
    def move_camera(self,direction):
        out=""
        if direction=="up":
           out="cam_up"
        elif direction=="down":
            out="cam_down"
        if out:
            self.__send(out)
    def move_car(self,direction):
        out=""
        if direction=="forward":
            out="move_forward"
        elif direction=="backward":
            out="move_backward"
        elif direction=="left":
            out="move_left"
        elif direction=="right":
            out="move_right"
        if out:
            self.__send(out)



motor_control=MotorControl()