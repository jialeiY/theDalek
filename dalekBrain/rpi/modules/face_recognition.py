import numpy as np
import face_recognition
import cv2

def recognize_face(img):

    face_locations = face_recognition.face_locations(img)

    for face_loc in face_locations:
        top = face_loc[0]
        right = face_loc[1]
        bottom = face_loc[2]
        left = face_loc[3]

        cv2.rectangle(img, (left,top), (right,bottom), (0,255,0), 2)
    return img