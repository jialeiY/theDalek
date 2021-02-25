import numpy as np
import cv2
import dlib
import time


face_cascade_detector = cv2.CascadeClassifier('../model/haarcascade_frontalface_default.xml')
hog_face_detector = dlib.get_frontal_face_detector()
cnn_face_detector = dlib.cnn_face_detection_model_v1("../model/mmod_human_face_detector.dat")


cap = cv2.VideoCapture(0)
cap.set(3,640) # set Width
cap.set(4,480) # set Height
font = cv2.FONT_HERSHEY_SIMPLEX

while True:
    ret, img = cap.read()
    # img = cv2.flip(img, -1)
    # gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    start=time.time()
    cascade_faces = face_cascade_detector.detectMultiScale(
        img,     
        scaleFactor=1.2,
        minNeighbors=5,     
        minSize=(20, 20)
    )
    cascade_duration=time.time()-start

    for (x,y,w,h) in cascade_faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        cv2.putText(img, "cascade "+str(cascade_duration), (x+5,y-5), font, 1, (255,0,0), 2)

    

    start=time.time()
    hog_faces=hog_face_detector(img,1)
    hog_duration=time.time()-start
    for hog_face in hog_faces:
        x = hog_face.left()
        y = hog_face.top()
        w = hog_face.right() - x
        h = hog_face.bottom() - y

        cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
        cv2.putText(img,"hog "+str(hog_duration), (x+5,y-5), font, 1, (0,255,0), 2)

    start=time.time()
    cnn_faces=cnn_face_detector(img,1)
    cnn_duration=time.time()-start
    for cnn_face in cnn_faces:
        x=cnn_face.rect.left()
        y=cnn_face.rect.top()
        w=cnn_face.rect.right()-x
        h=cnn_face.rect.bottom()-y

        cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)
        cv2.putText(img, "cnn "+str(cnn_duration), (x+5,y-5), font, 1, (0,0,255), 2)

    cv2.imshow('video',img)
    k = cv2.waitKey(30) & 0xff
    if k == 27: # press 'ESC' to quit
        break
cap.release()
cv2.destroyAllWindows()