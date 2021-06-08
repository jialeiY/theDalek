import cv2

from brain.config import DALEK_MODEL_PATH,DALEK_LABEL_PATH
import os
from nnLib.ssd.mobilenetv1_ssd import create_mobilenetv1_ssd_predictor,create_mobilenetv1_ssd

class DaleksRecognizer(object):

    def __init__(self,model_path,label_path,scale=0.5,threshold=0.5):
        self.model_path=model_path
        self.label_path=label_path

        self.labels=None
        self.model=None

        self.scale=scale
        self.threshold=threshold

        self.load_model(model_path)
        print("load dalek model done")

    def load_model(self,model_path):

        self.labels=[name.strip() for name in open(self.label_path).readlines()]

        net=create_mobilenetv1_ssd(len(self.labels), is_test=True)

        net.load(self.model_path)

        self.model = create_mobilenetv1_ssd_predictor(net, candidate_size=200)


    def recognize(self,img):

        if img is None:
            return img,False
        
        img=img.copy()
        font=cv2.FONT_HERSHEY_SIMPLEX
        small_img= cv2.resize(img, (0, 0), fx=self.scale, fy=self.scale)

        boxes, labels, probs = self.model.predict(small_img, 10,self.threshold)
    
        
        for i in range(boxes.size(0)):
            
            box = boxes[i, :]
            top = int(box[1]/self.scale)
            right = int(box[2]/self.scale)
            bottom = int(box[3]/self.scale)
            left = int(box[0]/self.scale)
            cv2.rectangle(img, (left,top), (right,bottom), (0,255,0), 2)

            label = f"{self.labels[labels[i]]}: {probs[i]:.2f}"

            cv2.putText(img, label,(left + 5, top +5), font,1,(255, 0, 255),2) 

        is_dalek_exist=boxes.size(0)>0
        return img,is_dalek_exist


# if __name__=="__main__":
#     dd=DaleksRecognizer(DALEK_MODEL_PATH,DALEK_LABEL_PATH)
#     img=cv2.imread('test_data/test_daleks.jpg')
#     img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
#     result=dd.recognize(img)
#     print(result)


    


        