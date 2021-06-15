import cv2
import os
from nnLib.ssd.mobilenetv1_ssd import create_mobilenetv1_ssd_predictor,create_mobilenetv1_ssd
from brain.actions.base_recognition import BaseRecognizer,RecognizerOutput


class DaleksRecognizer(BaseRecognizer):

    def __init__(self,model_path,label_path,scale=0.5,threshold=0.5):
        self.model_path=model_path
        self.label_path=label_path

        self.labels=None
        self.model=None

        self.scale=scale
        self.threshold=threshold

        self._load_model()
        print("load dalek model done")
    
    def get_name(self):
        return "DaleksRecognizer"

    def _load_model(self):

        self.labels=[name.strip() for name in open(self.label_path).readlines()]

        net=create_mobilenetv1_ssd(len(self.labels), is_test=True)

        net.load(self.model_path)

        self.model = create_mobilenetv1_ssd_predictor(net, candidate_size=200)


    def recognize(self,img):

        if img is None:
            return []
        
        img=img.copy()
        small_img= cv2.resize(img, (0, 0), fx=self.scale, fy=self.scale)

        boxes, labels, probs = self.model.predict(small_img, 10,self.threshold)

    
        output=[]
        for i in range(boxes.size(0)):

            box = boxes[i, :]
            output.append(RecognizerOutput(label=self.labels[labels[i]],
                             score=probs[i],
                             x0=int(box[0]/self.scale),
                             y0=int(box[1]/self.scale),
                             x1=int(box[2]/self.scale),
                             y1=int(box[3]/self.scale)))
        return output
