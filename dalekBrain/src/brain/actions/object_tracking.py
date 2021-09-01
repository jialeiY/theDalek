
# run after every object recognition
# input bounding boxes and labels with id
# return buchongde label and new id info
# (only give action when new object occur)

from typing import List
from brain.actions.base_recognition import RecognizerOutput

class CentroidObjectTracker(object):

    def __init__(self):

        self.next_id=0
        self.existing_objs={}
        self.disappeared_objs={}
        self.timeout=0

    def track(self,objects:List[RecognizerOutput])->List[RecognizerOutput]:

        pass

    def _calc_centroid(self):
        pass