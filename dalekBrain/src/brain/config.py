import os

VISION_WIDTH= 480
VISION_HEIGHT= 340

CAMERA_NAME=os.environ.get('CAMERA_NAME',"jetsoncamera")

# face recognition config
FACE_MODEL_PATH="../model/face/encodings.csv"
FACE_DETECTED_SOUND="../model/audio/exterminate.mp3"
FACE_SCALE=0.5
FACE_THR=0.5

# dalek recognition config
DALEK_MODEL_PATH="../model/dalek/dalek.pth"
DALEK_LABEL_PATH="../model/dalek/labels.txt"
DALEK_DETECTED_SOUND="../model/audio/goStronger.mp3"
DALEK_SCALE=1
DALEK_THR=0.9

DALEK_FACE_DETECTED_SOUND=""


# test_file config
IS_SAVE_OUTPUT=True
VISION_TEST_PATH="test_data/vision_output"

# rules
# rules={
#     "rules":[
#         {"action":["FaceRecognizer"],"output":FACE_DETECTED_SOUND},
#         {"action":["DaleksRecognizer"],"output":DALEK_DETECTED_SOUND},
#         {"action":["FaceRecognizer","DaleksRecognizer"],"output":DALEK_FACE_DETECTED_SOUND}
#     ]}

# }