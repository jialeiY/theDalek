import subprocess
import threading

class Speaker(object):

    def __init__(self):
        self._sound=None
        self.condition=threading.Condition()

    def _check_sound_available(self):
        return self.get_sound() is not None

    def start(self):

        with self.condition:
            self.condition.wait_for(self._check_sound_available)
        self.play_sound()

    def set_sound(self,sound):
        self._sound=sound

    def get_sound(self):
        return self._sound

    def play_sound(self):
        subprocess.run(["play", self.get_sound()])
        self.set_sound(None)


