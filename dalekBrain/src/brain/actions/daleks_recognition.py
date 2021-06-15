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

    def _predict(self,img):
        boxes, label_ids, probs = self.model.predict(img, 10,self.threshold)
        
        labels=[self.labels[i] for i in label_ids]

        return boxes,labels,probs
