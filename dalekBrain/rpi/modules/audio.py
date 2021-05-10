import subprocess
import threading

class Audio(object):

    def __init__(self):
        self.sound=None

        self.condition=threading.Condition()
        self.thread=threading.Thread(target=self._thread)
        self.thread.start()

    def _thread(self):
        while True:
            with self.condition:
                self.condition.wait()
            self.play_sound()

    def play_sound(self):
        if self.sound:
            subprocess.run(["play", self.sound])


