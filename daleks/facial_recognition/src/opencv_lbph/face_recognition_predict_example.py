import cv2
import numpy as np
import os 
import pandas as pd
import dlib


cascadePath = "../model/haarcascade_frontalface_default.xml"
faceCascade = cv2.CascadeClassifier(cascadePath)
font = cv2.FONT_HERSHEY_SIMPLEX

hog_face_detector = dlib.get_frontal_face_detector()


#local binary pattern histogram
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read('../model/face_recognize_lbph.yml')

#iniciate id counter
id = 0
# names related to ids: example ==> Marcelo: id=1,  etc
label_map=pd.read_csv("../model/face_recognize_lbph_labelmap.csv",index_col=0)
id2label=dict(label_map.values)

names = ['None', 'Marcelo', 'Paula', 'Ilza', 'Z', 'W'] 
# Initialize and start realtime video capture
cam = cv2.VideoCapture(0)
cam.set(3, 640) # set video widht
cam.set(4, 480) # set video height
# Define min window size to be recognized as a face
minW = 0.1*cam.get(3)
minH = 0.1*cam.get(4)
while True:
    ret, img =cam.read()
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
    faces = faceCascade.detectMultiScale( 
        gray,
        scaleFactor = 1.2,
        minNeighbors = 5,
        minSize = (int(minW), int(minH)),
       )

    faces_hog = hog_face_detector(gray, 1)

    for face in faces_hog:
        x = face.left()
        y = face.top()
        w = face.right() - x
        h = face.bottom() - y

        # draw box over face
        cv2.rectangle(img, (x,y), (x+w,y+h), (0,255,0), 2)

        id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
        # Check if confidence is less them 100 ==> "0" is perfect match 
        if (confidence < 100):
            label=id2label.get(id,"unknown")
            confidence = "  {0}%".format(round(100 - confidence))
        else:
            label = "unknown"
            confidence = "  {0}%".format(round(100 - confidence))
        
        cv2.putText(img, str(label), (x+5,y-5), font, 1, (255,255,255), 2)
        cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)  


    for(x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (255,0,0), 2)
    #     id, confidence = recognizer.predict(gray[y:y+h,x:x+w])
    #     # Check if confidence is less them 100 ==> "0" is perfect match 
    #     if (confidence < 100):
    #         label=id2label.get(id,"unknown")
    #         confidence = "  {0}%".format(round(100 - confidence))
    #     else:
    #         label = "unknown"
    #         confidence = "  {0}%".format(round(100 - confidence))
        
    #     cv2.putText(img, str(label), (x+5,y-5), font, 1, (255,255,255), 2)
    #     cv2.putText(img, str(confidence), (x+5,y+h-5), font, 1, (255,255,0), 1)  
    
    cv2.imshow('camera',img) 
    k = cv2.waitKey(10) & 0xff # Press 'ESC' for exiting video
    if k == 27:
        break
# Do a bit of cleanup
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()