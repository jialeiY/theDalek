import os

VISION_WIDTH= 480
VISION_HEIGHT=340

CAMERA_NAME=os.environ.get('CAMERA_NAME',"jetsoncamera")

# face recognition config
FACE_MODEL_PATH="../model/face/encodings.csv"
FACE_DETECTED_SOUND="../model/audio/exterminate.mp3"
FACE_SCALE=0.5
FACE_THR=0.5




DALEK_DETECTION_MODEL="../model/dalek.pth"