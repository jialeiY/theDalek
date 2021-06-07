import os

VISION_WIDTH= 480
VISION_HEIGHT=340

CAMERA_NAME=os.environ.get('CAMERA_NAME',"mockcamera")

# face recognition config
FACE_MODEL_PATH="../model/face/encodings.csv"
FACE_DETECTED_SOUND="../model/audio/exterminate.mp3"
FACE_SCALE=0.5
FACE_THR=0.5

# dalek recognition config
DALEK_MODEL_PATH="../model/dalek/dalek.pth"
DALEK_LABEL_PATH="../model/dalek/labels.txt"
DALEK_DETECTED_SOUND="../model/audio/tardis.mp3"