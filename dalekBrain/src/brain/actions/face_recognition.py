import numpy as np
import face_recognition
import cv2
import csv
import os
from brain.actions.base_recognition import BaseRecognizer


def _load_face_encodings(file_path,prefix=""):
    face_labels=[]
    face_encodings=[]
    with open(file_path,newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        next(reader)
        for row in reader:
            name=row[0]
            encoding=np.asarray(row[1:],dtype=np.float64)

            face_labels.append(prefix+name)
            face_encodings.append(encoding)
    return face_encodings,face_labels

def _write_to_face_encodings(file_path,fields):
    with open(file_path,'a',newline='') as csvfile:
        writer = csv.writer(csvfile)
        csvfile.write("\n")
        writer.writerow(fields)

class FaceRecognizerTrainer(object):

    def __init__(self,camera,encodings_path):
        self.camera=camera
        self.encodings_path=encodings_path
    
    def add_face(self,face_name,scale=0.5):
        exist_face_encodings,exist_face_labels=_load_face_encodings(self.encodings_path)
        if(face_name in exist_face_labels):
            print(exist_face_labels)
            raise Exception("face name already exist!")

        try:
            face_encodings=[]
            counter=0
            while(counter<5):
                img = self.camera.get_raw_img()
                print(counter,img.shape)
                
                small_img= cv2.resize(img, (0, 0), fx=scale, fy=scale)

                face_locations = face_recognition.face_locations(small_img,model="hog")
                face_encodings +=face_recognition.face_encodings(small_img, face_locations)

                counter+=1

            print(f"Add face done! {len(face_encodings)} {face_encodings[0].shape}")
            mean_face_encoding=np.asarray(face_encodings).mean(axis=0)

            csv_fields=[face_name]+mean_face_encoding.tolist()
            _write_to_face_encodings(self.encodings_path,csv_fields)

        except Exception as e:
            print(f"add face {face_name} error: ",str(e))
            raise Exception(f"add face error!")





class FaceRecognizer(BaseRecognizer):

    
    def __init__(self,model_path,scale=0.5,threshold=0.35):

        self.model_path=model_path
        self.scale=scale
        self.threshold=threshold
        
        self.face_labels=[]
        self.face_encodings=[]

        self.unknwon_label="face_unknown"
        self.label_prefix="face_"

        self._load_model()
    
    def get_name(self):
        return "FaceRecognizer"
        
    def _load_model(self):
        self.face_encodings,self.face_labels=_load_face_encodings(self.model_path,self.label_prefix)
    
    def _predict(self,img):

        face_locations = face_recognition.face_locations(img,model="hog")
        face_encodings = face_recognition.face_encodings(img, face_locations)

        labels=[]
        probs=[]

        for face_encoding in face_encodings:
            name=self.unknwon_label
            face_score=1

            if self.face_encodings:
                face_distances = face_recognition.face_distance(self.face_encodings, face_encoding)
                best_match_index = np.argmin(face_distances)
                face_score=face_distances[best_match_index]
                if face_score<=self.threshold:
                    name=self.face_labels[best_match_index]

            labels.append(name)
            probs.append(1-face_score)


        boxes=[(loc[3],loc[0],loc[1],loc[2]) for loc in face_locations]
        
        return boxes,labels,probs
