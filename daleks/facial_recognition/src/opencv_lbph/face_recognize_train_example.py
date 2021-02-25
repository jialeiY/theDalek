import cv2
import numpy as np
from PIL import Image
import os
import pandas as pd
# Path for face image database
path = '../data/small_lfw'
recognizer = cv2.face.LBPHFaceRecognizer_create()
detector = cv2.CascadeClassifier("../model/haarcascade_frontalface_default.xml");
# function to get the images and label data
def getImagesAndLabels(path):
    id2name={}
    dirPaths = [os.path.join(path,f) for f in os.listdir(path) if os.path.isdir(os.path.join(path,f))]     
    faceSamples=[]
    ids = []
    for i,dirPath in enumerate(dirPaths):

        label=os.path.basename(dirPath)
        id2name[i]=label

        for imageFile in os.listdir(dirPath):
            if imageFile.endswith(".jpg"):
                imagePath=os.path.join(dirPath,imageFile)

                PIL_img = Image.open(imagePath).convert('L') # convert it to grayscale
                img_numpy = np.array(PIL_img,'uint8')
                faces = detector.detectMultiScale(img_numpy)
                for (x,y,w,h) in faces:
                    faceSamples.append(img_numpy[y:y+h,x:x+w])
                    ids.append(i)
    df=pd.DataFrame(id2name.items(),columns=["id","name"])
    df.to_csv("../model/face_recognize_lbph_labelmap.csv")
    return faceSamples,ids
print ("\n [INFO] Training faces. It will take a few seconds. Wait ...")
faces,ids = getImagesAndLabels(path)
recognizer.train(faces, np.array(ids))
# Save the model into trainer/trainer.yml
recognizer.write('../model/face_recognize_lbph.yml') # recognizer.save() worked on Mac, but not on Pi
# Print the numer of faces trained and end program
print("\n [INFO] {0} faces trained. Exiting Program".format(len(np.unique(ids))))