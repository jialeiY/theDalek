import numpy as np
import face_recognition
import cv2
import csv


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


class FaceRecognizer(object):

    
    def __init__(self,face_encoding_path):
        
        self.face_labels=[]
        self.face_encodings=[]

        self._load_face_encodings(face_encoding_path)

    def _load_face_encodings(self,file_path):

        with open(file_path, newline='') as csvfile:
            reader = csv.reader(csvfile, delimiter=',')
            next(reader)
            for row in reader:
                name=row[0]
                encoding=np.asarray(row[1:],dtype=np.float64)

                self.face_labels.append(name)
                self.face_encodings.append(encoding)
    
    def add_face(self):
        # 1. capture photo
        # 2. detection face
        # 3. calculate face encoding
        # 4. save to encoding file
        pass
    
    def recognize(self,img,scale=0.5,threshold=0.5):
        font=cv2.FONT_HERSHEY_SIMPLEX
        small_img= cv2.resize(img, (0, 0), fx=scale, fy=scale)
    
        face_locations = face_recognition.face_locations(small_img,model="hog")
        face_encodings = face_recognition.face_encodings(small_img, face_locations)

        face_names=[]
        face_dists=[]

        for face_encoding in face_encodings:
            face_distances = face_recognition.face_distance(self.face_encodings, face_encoding)
            best_match_index = np.argmin(face_distances)

            name="unknown"
            if face_distances[best_match_index]<=threshold:
                name=self.face_labels[best_match_index]
            face_names.append(name)
            face_dists.append(face_distances[best_match_index])
        
        for face_loc,name,dist in zip(face_locations,face_names,face_dists):
            top = int(face_loc[0]/scale)
            right = int(face_loc[1]/scale)
            bottom = int(face_loc[2]/scale)
            left = int(face_loc[3]/scale)

            cv2.rectangle(img, (left,top), (right,bottom), (0,255,0), 2)
            cv2.putText(img, str(name), (left+5,top-5), font, 1, (255,255,255), 2)
            cv2.putText(img, f"{dist:.2f}", (left+5,top-20), font, 1, (255,255,255), 2)
        return img

