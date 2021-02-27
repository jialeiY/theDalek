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

        with picamera.PiCamera() as camera:
            time.sleep(2)
            stream=io.BytesIO()
            for _  in camera.capture_continuous(stream,format="mjpeg",use_video_port=True):
                
                stream.seek(0)
                yield stream.read()

                # reset stream for next frame
                stream.seek(0)
                stream.truncate()


class MockCamera(BaseCamera):

    imgs = [open(f + '.jpg', 'rb').read() for f in ['1', '2', '3']]

    @staticmethod
    def frames():
        while True:
            time.sleep(1)
            yield MockCamera.imgs[int(time.time()) % 3]

