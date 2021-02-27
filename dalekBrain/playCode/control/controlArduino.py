import serial
from time import sleep


ser=serial.Serial("/dev/ttyACM0",9600)

while True:
    val=input("1.move\n2.camera\n")
    val=int(val)
    out=None 
    if val==1:
        move_val=input("1.forward\n0.backward\n2.left\n3.right\n00.stop\n")
        if move_val==1:
            out="forward"
        elif move_val=="0":
            out="backward"
        elif move_val=="2":
            out="left"
        elif move_val=="3":
            out="right"
        elif move_val=="00":
            out="stop"
    elif val==2:
        camera_val=input("0-180\n")
        out=str(camera_val)
    else:
        print()
    if out is not None:
        ser.write(out.encode())
