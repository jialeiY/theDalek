import io
import time
import threading
import numpy as np
import cv2
from modules.face_recognition import recognize_face,FaceRecognizer
from config import FACE_ENCODING_PATH
class CameraFactory(object):

    @staticmethod
    def create_camera(name):
        if name.lower()=="picamera":
            return PiCamera()
        elif name.lower()=="mockcamera":
            return MockCamera()
        elif name.lower()=="opencvcamera":
            return OpenCVCamera()
        else:
            raise Exception("no such camera")

class BaseCamera(object):
    thread=None
    frame=None
    last_access=0
    condition=None
    face_recognizer=FaceRecognizer(FACE_ENCODING_PATH)
    
    def __init__(self):
        if BaseCamera.thread is None:
            BaseCamera.last_access=time.time()

            BaseCamera.condition=threading.Condition()
            BaseCamera.thread=threading.Thread(target=self._thread)
            BaseCamera.thread.start()

            while self.get_frame() is None:
                time.sleep(0)

    def get_frame(self):
        BaseCamera.last_access=time.time()
        with BaseCamera.condition:
            BaseCamera.condition.wait()
        return BaseCamera.frame

    @staticmethod
    def frames():
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


class PiCamera(BaseCamera):

    @staticmethod
    def frames():
        import picamera
        WIDTH=320
        HEIGHT=240

        with picamera.PiCamera(framerate=10) as camera:
            camera.resolution = (WIDTH, HEIGHT)

            time.sleep(2)

            output = np.empty((HEIGHT, WIDTH, 3), dtype=np.uint8)

            process_this_frame = True

            for _  in camera.capture_continuous(output,format="rgb",use_video_port=True):
                

                #recognized_output=recognize_face(output)
                recognized_output=PiCamera.face_recognizer.recognize(output)
                recognized_output=cv2.cvtColor(recognized_output , cv2.COLOR_RGB2BGR)

                yield cv2.imencode(".jpg",recognized_output)[1].tobytes()


class OpenCVCamera(BaseCamera):

    @staticmethod
    def frames():
        camera = cv2.VideoCapture(0)
        camera.set(3,320) # set Width
        camera.set(4,240) # set Height
        if not camera.isOpened():
            raise RuntimeError('Could not start camera.')

        while True:
            # read current frame
            _, img = camera.read()
            recognized_output=recognize_face(img)
            # encode as a jpeg image and return it
            yield cv2.imencode('.jpg', recognized_output)[1].tobytes()


class MockCamera(BaseCamera):

    imgs = [open("static/"+f + '.jpg', 'rb').read() for f in ['1', '2', '3']]

    @staticmethod
    def frames():
        while True:
            time.sleep(1)
            yield MockCamera.imgs[int(time.time()) % 3]
