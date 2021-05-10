import io
import time
import threading
import numpy as np
import cv2
from modules.utils.singleton import singleton

WIDTH=480
HEIGHT=320

class CameraFactory(object):

    @staticmethod
    def create_camera(name):
        if name.lower()=="picamera":
            return PiCamera()
        elif name.lower()=="mockcamera":
            return MockCamera()
        elif name.lower()=="opencvcamera":
            return OpenCVCamera()
        elif name.lower()=="jetsoncamera":
            return JetsonCamera()
        else:
            raise Exception("no such camera")

class BaseCamera(object):
    thread=None
    frame=None
    last_access=0
    condition=None
    
    def __init__(self):
        print("init camera")
        if BaseCamera.thread is None:
            BaseCamera.last_access=time.time()

            BaseCamera.condition=threading.Condition()
            BaseCamera.thread=threading.Thread(target=self._thread)
            BaseCamera.thread.start()
            print("init camera thread")

            while self.get_frame() is None:
                time.sleep(0)



    def get_frame(self):
        BaseCamera.last_access=time.time()
        with BaseCamera.condition:
            BaseCamera.condition.wait()
        return BaseCamera.frame
    

    @classmethod
    def frames(cls):
        raise RuntimeError('Must be implemented by subclasses.')

    @classmethod
    def _thread(cls):
        print('Starting camera thread.')
        frames_iterator=cls.frames()
        for frame in frames_iterator:
            with BaseCamera.condition:

                BaseCamera.frame=frame
                BaseCamera.condition.notify_all()


            time.sleep(0)

            if time.time() - BaseCamera.last_access > 10:
                frames_iterator.close()
                print('Stopping camera thread due to inactivity.')
                break
        BaseCamera.thread = None

@singleton
class JetsonCamera(BaseCamera):


    @staticmethod
    def _get_jetson_gstreamer_source(capture_width=640, capture_height=480, display_width=640, display_height=480, framerate=15, flip_method=0):
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


    @classmethod
    def frames(cls):

        camera = cv2.VideoCapture(cls._get_jetson_gstreamer_source(display_width=WIDTH,display_height=HEIGHT,flip_method=2), cv2.CAP_GSTREAMER)

        if not camera.isOpened():
            raise RuntimeError('Could not start camera.')

        while True:
            # read current frame
            _, output_stream = camera.read()
            
            if output_stream is not None:
                output_stream=cv2.cvtColor(output_stream , cv2.COLOR_BGR2RGB)


            yield output_stream



    
@singleton
class PiCamera(BaseCamera):

    face_recognizer=None

    @classmethod
    def frames(cls):
        import picamera

        with picamera.PiCamera(framerate=10) as camera:
            camera.resolution = (WIDTH, HEIGHT)

            time.sleep(2)

            output_stream = np.empty((HEIGHT, WIDTH, 3), dtype=np.uint8)


            for _  in camera.capture_continuous(output_stream,format="rgb",use_video_port=True):
                
                yield output_stream


class OpenCVCamera(BaseCamera):

    @classmethod
    def frames(cls):
        camera = cv2.VideoCapture(0)
        camera.set(3,WIDTH) # set Width
        camera.set(4,HEIGHT) # set Height
        if not camera.isOpened():
            raise RuntimeError('Could not start camera.')

        while True:
            # read current frame
            _, img = camera.read()
            # encode as a jpeg image and return it
            yield img


class MockCamera(BaseCamera):

    imgs = [open("static/"+f + '.jpg', 'rb').read() for f in ['1', '2', '3']]

    @classmethod
    def frames(cls):
        while True:
            time.sleep(1)
            yield MockCamera.imgs[int(time.time()) % 3]
