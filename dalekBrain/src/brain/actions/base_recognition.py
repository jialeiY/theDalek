
class RecognizerOutput(object):
    def __init__(self,label,score,x0,y0,x1,y1):
        self.label=label
        self.score=score

        self.x0=x0 #left
        self.y0=y0  #top
        self.x1=x1  #right
        self.y1=y1  #bottom
        
class BaseRecognizer(object):

    def recognize(self,img):
        pass

    def get_name(self):
        pass
