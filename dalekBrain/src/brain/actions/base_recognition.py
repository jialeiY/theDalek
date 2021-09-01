import cv2

class RecognizerOutput(object):
    def __init__(self,label,score,x0,y0,x1,y1):
        self.label=label
        self.score=score

        self.x0=x0  #left
        self.y0=y0  #top
        self.x1=x1  #right
        self.y1=y1  #bottom

        self.id=None
        self.new_obj=True
        
class BaseRecognizer(object):

    def __init__(self,scale):
        self.scale=scale

    def recognize(self,img):
        if img is None:
            return []
        
        img=img.copy()
        small_img= cv2.resize(img, (0, 0), fx=self.scale, fy=self.scale)
    
        boxes,labels,probs=self._predict(small_img)
        
        output=[]
        for box,label,prob in zip(boxes,labels,probs):


            output.append(RecognizerOutput(label=label,
                    score=prob,
                    x0=int(box[0]/self.scale),
                    y0=int(box[1]/self.scale),
                    x1=int(box[2]/self.scale),
                    y1=int(box[3]/self.scale)))


        return output

    def _predict(self,img):
        pass

    def get_name(self):
        pass
