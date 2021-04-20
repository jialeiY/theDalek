import serial

class CamMotor(object):

    def __init__(self):
        self.ser=serial.Serial("/dev/ttyACM0",9600)
        self.current_pos=90
    
    def move(self,direction):
        
        if direction=="up":
           out="cam_up"
        elif direction=="down":
            out="cam_down"

        self.ser.write(out.encode())


cam_motor_obj=CamMotor()