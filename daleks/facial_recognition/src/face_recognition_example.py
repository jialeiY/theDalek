import face_recognition
import cv2
import dlib
import os
import numpy as np


# 1 init face detector
# 2 init face recognizer
# 3 load known face dataset
# 4 compute embedding for known face dataset
# 5 init video
# 6 loop
#   6.1 take frame
#   6.2 face detect
#   6.3 compute embedding
#   6.4 loop compare with known face
#   6.5 take most similar one

threshold=0.4
font=cv2.FONT_HERSHEY_SIMPLEX

# 3 
known_faces_dataset="../data/small_lfw"
known_faces_lables=[]
known_faces_paths=[]
known_faces_encodings=[]

print("getting all known faces....")
for person_name in os.listdir(known_faces_dataset):
    person_dir_path=os.path.join(known_faces_dataset,person_name)
    if os.path.isdir(person_dir_path):
        for person_img_name in os.listdir(person_dir_path):
            img_path=os.path.join(person_dir_path,person_img_name)

            try:
                img=cv2.imread(img_path)
                img=cv2.cvtColor(img,cv2.COLOR_BGR2RGB)
                face_locations = face_recognition.face_locations(img)
                if len(face_locations)>0:
                    face_encoding = face_recognition.face_encodings(img, face_locations)[0]
                    known_faces_lables.append(person_name)
                    known_faces_paths.append(os.path.join(person_dir_path,person_img_name))
                    known_faces_encodings.append(face_encoding)
                else:
                    print(f"no face found in {img_path}")
            except Exception as e:
                print(img_path,str(e))

          
print(f"have {len(known_faces_paths)} known faces")


# 5
cap = cv2.VideoCapture(0)
cap.set(3,640) # set Width
cap.set(4,480) # set Height

while True:
    ret, raw_img = cap.read()

    img = cv2.cvtColor(raw_img,cv2.COLOR_BGR2RGB)
    face_locations = face_recognition.face_locations(img)
    face_encodings = face_recognition.face_encodings(img, face_locations)

    face_names=[]
    face_dists=[]
    for face_encoding in face_encodings:
        face_distances = face_recognition.face_distance(known_faces_encodings, face_encoding)
        best_match_index = np.argmin(face_distances)

        name="unknown"
        if face_distances[best_match_index]<=threshold:
            name=known_faces_lables[best_match_index]
        face_names.append(name)
        face_dists.append(face_distances[best_match_index])
    
    for face_loc,name,dist in zip(face_locations,face_names,face_dists):
        top = face_loc[0]
        right = face_loc[1]
        bottom = face_loc[2]
        left = face_loc[3]

        cv2.rectangle(raw_img, (left,top), (right,bottom), (0,255,0), 2)
        cv2.putText(raw_img, str(name), (left+5,top-5), font, 1, (255,255,255), 2)
        cv2.putText(raw_img, f"{dist:.2f}", (left+5,top-20), font, 1, (255,255,255), 2)

    cv2.imshow('Video', raw_img)
    if cv2.waitKey(1) & 0xFF == 27:
        break
cap.release()
cv2.destroyAllWindows()
        



    


