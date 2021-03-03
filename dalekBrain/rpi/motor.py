import serial

class CamMotor(object):

    def __init__(self):
        self.ser=serial.Serial("/dev/ttyACM0",9600)
        self.current_pos=90
    
    def move(self,direction):
        
        if direction=="up":
            self.current_pos=min(self.current_pos+1,180)
        elif direction=="down":
            self.current_pos=max(self.current_pos-1,0)

        
        print(f"camera position {self.current_pos}")
        self.ser.write(str(self.current_pos).encode())


cam_motor_obj=CamMotor()