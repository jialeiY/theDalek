import io
import time
import threading
import numpy as np
import cv2
from os.path import join,abspath,dirname


class CameraFactory(object):

    @staticmethod
    def create_camera(name,**kwargs):
        if name.lower()=="picamera":
            return PiCamera(**kwargs)
        elif name.lower()=="mockcamera":
            return MockCamera(**kwargs)
        elif name.lower()=="opencvcamera":
            return OpenCVCamera(**kwargs)
        elif name.lower()=="jetsoncamera":
            return JetsonCamera(**kwargs)
        else:
            raise Exception("no such camera")

class BaseCamera(object):

    def __init__(self,width,height):
        
        self.width=width
        self.height=height
        self.frame=None
        self.last_access=0
        self.condition=threading.Condition()


    def get_frame(self):
        self.last_access=time.time()
        with self.condition:
            self.condition.wait()
        return self.frame
    

    def frames(self):
        raise RuntimeError('Must be implemented by subclasses.')

    def start(self):
        print('Starting camera thread.')
        self.last_access=time.time()

        frames_iterator=self.frames()
        for frame in frames_iterator:
            with self.condition:

                self.frame=frame
                self.condition.notify_all()

            time.sleep(0)

            if time.time() - self.last_access > 10:
                frames_iterator.close()
                print('Stopping camera thread due to inactivity.')
                break


class JetsonCamera(BaseCamera):



    def _get_jetson_gstreamer_source(self,capture_width=640, capture_height=480, display_width=640, display_height=480, framerate=15, flip_method=0):
        """
        Return an OpenCV-compatible video source description that uses gstreamer to capture video from the RPI camera on a Jetson Nano
        """
        return (
                f'nvarguscamerasrc ! video/x-raw(memory:NVMM), ' +
                f'width=(int){capture_width}, height=(int){capture_height}, ' +
                f'format=(string)NV12, framerate=(fraction){framerate}/1 ! ' +
                f'nvvidconv flip-method={flip_method} ! ' +
                f'video/x-raw, width=(int){display_width}, height=(int){display_height}, format=(string)BGRx ! ' +
                'videoconvert ! video/x-raw, format=(string)BGR ! appsink'
                )



    def frames(self):

        camera = cv2.VideoCapture(self._get_jetson_gstreamer_source(display_width=self.width,display_height=self.height,flip_method=2), cv2.CAP_GSTREAMER)

        if not camera.isOpened():
            raise RuntimeError('Could not start camera.')

        while True:
            # read current frame
            _, output_stream = camera.read()
            
            if output_stream is not None:
                output_stream=cv2.cvtColor(output_stream , cv2.COLOR_BGR2RGB)


            yield output_stream



    

class PiCamera(BaseCamera):


    def frames(self):
        import picamera

        with picamera.PiCamera(framerate=10) as camera:
            camera.resolution = (self.width, self.height)

            time.sleep(2)

            output_stream = np.empty((self.height, self.width, 3), dtype=np.uint8)


            for _  in camera.capture_continuous(output_stream,format="rgb",use_video_port=True):
                
                yield output_stream


class OpenCVCamera(BaseCamera):


    def frames(self):
        camera = cv2.VideoCapture(0)
        camera.set(3,self.width) # set Width
        camera.set(4,self.height) # set Height
        if not camera.isOpened():
            raise RuntimeError('Could not start camera.')

        while True:
            # read current frame
            _, img = camera.read()
            # encode as a jpeg image and return it
            yield img


class MockCamera(BaseCamera):

    imgs = [open(join(dirname(abspath(__file__)),f"data/mock{n}.jpg"), 'rb').read() for n in ['1', '2', '3']]

    def frames(self):
        while True:
            time.sleep(1)
            yield MockCamera.imgs[int(time.time()) % 3]
