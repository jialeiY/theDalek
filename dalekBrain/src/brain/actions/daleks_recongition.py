import jetson.inference
import jetson.utils
import sys
import torch
from config import DALEK_DETECTION_MODEL
import cv2

class DaleksRecognizer(object):

    def __init__(self,model_path):
        self.model_path=model_path

        self.model=self.load_model(model_path)

    def load_model(self,model_path):
        model = Net()
        model.load_state_dict(torch.load(model_path))
        model.eval()

    def recognize(self,img,scale=0.5,threshold=0.5):
        result=self.model.forward(img)
        return result


if __name__=="__main__":
    dd=DaleksRecognizer(DALEK_DETECTION_MODEL)
    img=cv2.imread('static/1.jpg')
    result=dd.recognize(img)
    print(result)

    


        