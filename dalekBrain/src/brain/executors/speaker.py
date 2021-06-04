import subprocess
import threading

class Speaker(object):

    def __init__(self):
        self._sound=None
        self.condition=threading.Condition()

    def start(self):
        print("speaker thread start")
        while True:
            with self.condition:
                self.condition.wait()

            self.play_sound()
        print("speaker thread end")

    def set_sound(self,sound):
        self._sound=sound

    def get_sound(self):
        return self._sound

    def play_sound(self):
        subprocess.run(["play", self.get_sound()])


