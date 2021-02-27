import io
import time
import threading

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
    
    def __init__(self):
        if BaseCamera.thread is None:
            BaseCamera.last_access=time.time()

            BaseCamera.thread=threading.Thread(target=self._thread)
            BaseCamera.thread.start()

            while self.get_frame() is None:
                time.sleep(0)

    def get_frame(self):
        BaseCamera.last_access=time.time()
        return BaseCamera.frame

    @staticmethod
    def frames():
        raise RuntimeError('Must be implemented by subclasses.')

    @classmethod
    def _thread(cls):
        print('Starting camera thread.')
        frames_iterator=cls.frames()
        for frame in frames_iterator:
            BaseCamera.frame=frame

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

        with picamera.PiCamera(resolution='320x240', framerate=24) as camera:
            time.sleep(2)
            stream=io.BytesIO()
            for _  in camera.capture_continuous(stream,format="jpeg",use_video_port=True):
                
                stream.seek(0)
                yield stream.read()

                # reset stream for next frame
                stream.seek(0)
                stream.truncate()


class OpenCVCamera(BaseCamera):

    @staticmethod
    def frames():
        import cv2
        camera = cv2.VideoCapture(0)
        camera.set(3,320) # set Width
        camera.set(4,240) # set Height
        if not camera.isOpened():
            raise RuntimeError('Could not start camera.')

        while True:
            # read current frame
            _, img = camera.read()

            # encode as a jpeg image and return it
            yield cv2.imencode('.jpg', img)[1].tobytes()


class MockCamera(BaseCamera):

    imgs = [open(f + '.jpg', 'rb').read() for f in ['1', '2', '3']]

    @staticmethod
    def frames():
        while True:
            time.sleep(1)
            yield MockCamera.imgs[int(time.time()) % 3]

