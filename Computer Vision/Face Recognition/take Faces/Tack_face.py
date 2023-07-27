# ---------------------------------------------------------------------------- #
# - For better result please make sure to press SPACE when your face is clear  #
#   then press another SPACE to quit                                           #
# ---------------------------------------------------------------------------- #
import cv2
import os
cap = cv2.VideoCapture(0)

if os.chdir(r'../My_PIC') is False:
    os.mkdir(r'../My_PIC')
os.chdir(r'../My_PIC')
while True:
    for i in range(0, 2):
        ret, Frame = cap.read()
        Frame = cv2.cvtColor(Frame, cv2.COLOR_BGR2GRAY)
        cv2.imwrite("Mario_"+str(0)+".jpg", Frame)

        cv2.imshow("My_Frame", Frame)
        cv2.waitKey(0)
    break
