
# run after every object recognition
# input bounding boxes and labels with id
# return buchongde label and new id info
# (only give action when new object occur)

from typing import List
from collections import OrderedDict
from scipy.spatial import distance_matrix
import numpy as np

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


class CentroidObjectTracker(object):

    def __init__(self):

        self.next_id=0
        self.existing_objs=OrderedDict()
        self.disappeared_objs={}
        self.timeout=0

    def track(self,objects:List[RecognizerOutput])->List[RecognizerOutput]:

        new_obj_centroids=np.asarray([self._calc_centroid(obj) for obj in objects])

        visited_rows=set()
        visited_cols=set()

        if len(self.existing_objs)>0:

            exist_obj_ids=list(self.existing_objs.keys())
            exist_obj_centroids=np.array(list(self.existing_objs.values()))

            dists=distance_matrix(exist_obj_centroids,new_obj_centroids)

            rows=dists.min(axis=1).argsort()
            cols=dists.argmin(axis=1)[rows]


            for row,col in zip(rows,cols):
                if row in visited_rows or col in visited_cols:
                    continue

                exist_id=exist_obj_ids[row]
                self.existing_objs[exist_id]=new_obj_centroids[col]
                self.disappeared_objs[exist_id]=0

                objects[col].is_new_obj=False
                objects[col].id=exist_id

                visited_cols.add(row)
                visited_cols.add(col)
            
        else:
            rows=[]
            cols=list(range(len(objects)))

        unseen_rows=set(rows)-visited_rows
        unseen_cols=set(cols)-visited_rows

        for row in unseen_rows:
            self.deregister(exist_obj_ids[row])

        for col in unseen_cols:
            id=self.register(new_obj_centroids[col])
            objects[col].id=id

        return objects


    def register(self,obj_centroid):

        self.existing_objs[self.next_id]=obj_centroid
        self.next_id+=1

        return  self.next_id-1


    def deregister(self,obj_id):
        disappear_duration=self.disappeared_objs.get(obj_id,0)+1

        if disappear_duration>self.timeout:
            del self.existing_objs[obj_id]
        else:
            self.disappeared_objs[obj_id]=disappear_duration

    def _calc_centroid(self,obj:RecognizerOutput):
        
        x=(obj.x0+obj.x1)/2
        y=(obj.y0+obj.y1)/2

        return x,y
    

if __name__=="__main__":
    tracker=CentroidObjectTracker()

    tracker.track([RecognizerOutput('dalek',1,1,1,2,2),RecognizerOutput('dalek',1,3,3,4,4)])

    tracker.track([RecognizerOutput('dalek',1,1.5,1.5,2.5,2.5),RecognizerOutput('dalek',1,2.5,2.5,3.5,3.5)])
