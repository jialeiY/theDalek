import numpy as np
import face_recognition
import cv2
from modules.utils.timer import timer

# @timer
def recognize_face(img,scale=0.5):

    small_img= cv2.resize(img, (0, 0), fx=scale, fy=scale)
    
    face_locations = face_recognition.face_locations(small_img,model="hog")

    for face_loc in face_locations:
        
        top = int(face_loc[0]/scale)
        right = int(face_loc[1]/scale)
        bottom = int(face_loc[2]/scale)
        left = int(face_loc[3]/scale)

        cv2.rectangle(img, (left,top), (right,bottom), (0,255,0), 2)
    return img