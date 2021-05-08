import subprocess

def play_sound(file:str):
    subprocess.run(["play", file])



def test_play_sound():
    file_path="../../model/audio/exterminate.mp3"
    play_sound(file_path)