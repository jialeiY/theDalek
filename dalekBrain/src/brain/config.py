import os

VISION_WIDTH= 480
VISION_HEIGHT=340

CAMERA_NAME=os.environ.get('CAMERA_NAME',"jetsoncamera")

FACE_ENCODING_PATH="../model/face/encodings.csv"
FACE_DETECTED_SOUND="../model/audio/exterminate.mp3"

DALEK_DETECTION_MODEL="../model/dalek.pth"