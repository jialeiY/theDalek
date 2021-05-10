import numpy as np
import face_recognition
import cv2
import csv
import os

FACE_ENCODING_PATH="../../model/face/encodings.csv"

def _load_face_encodings(file_path):
    face_labels=[]
    face_encodings=[]
    with open(file_path,newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        next(reader)
        for row in reader:
            name=row[0]
            encoding=np.asarray(row[1:],dtype=np.float64)

            face_labels.append(name)
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





class FaceRecognizer(object):

    
    def __init__(self,face_encoding_path):
        
        self.face_encoding_path=face_encoding_path

        self.face_labels=[]
        self.face_encodings=[]

        self.load_face_encodings()
        
    def load_face_encodings(self):
        self.face_encodings,self.face_labels=_load_face_encodings(self.face_encoding_path)

    def recognize(self,img,scale=0.5,threshold=0.35):
        img=img.copy()
        font=cv2.FONT_HERSHEY_SIMPLEX
        small_img= cv2.resize(img, (0, 0), fx=scale, fy=scale)
    
        face_locations = face_recognition.face_locations(small_img,model="hog")
        face_encodings = face_recognition.face_encodings(small_img, face_locations)

        face_names=[]
        face_dists=[]

        for face_encoding in face_encodings:
            name="unknown"
            face_score=1

            if self.face_encodings:
                face_distances = face_recognition.face_distance(self.face_encodings, face_encoding)
                best_match_index = np.argmin(face_distances)
                face_score=face_distances[best_match_index]
                if face_score<=threshold:
                    name=self.face_labels[best_match_index]

            face_names.append(name)
            face_dists.append(1-face_score)
        
        for face_loc,name,dist in zip(face_locations,face_names,face_dists):
            top = int(face_loc[0]/scale)
            right = int(face_loc[1]/scale)
            bottom = int(face_loc[2]/scale)
            left = int(face_loc[3]/scale)

            cv2.rectangle(img, (left,top), (right,bottom), (0,255,0), 2)
            cv2.putText(img, str(name), (left+5,top-5), font, 1, (255,255,255), 2)
            cv2.putText(img, f"{dist:.2f}", (left+5,top-20), font, 1, (255,255,255), 2)
        
        is_face_exist=len(face_names)>0
        return img,is_face_exist

