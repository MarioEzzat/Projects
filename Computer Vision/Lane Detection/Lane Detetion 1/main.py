
import cv2
import numpy as np
import Region_of_intrest
import Canny
import Display_lines
import Combin_Lines
import DETECTION

################################################
# insert video or camera
################################################
# Test Cases:-  street.mp4 - street2.mp4
cap = cv2.VideoCapture('street2.mp4')
_, img = cap.read()
################################################

while _ is True:

    _, img = cap.read()
    # resize the frame
    ing = cv2.resize(img, None, fx=0.8, fy=0.8)
    # copy the img to make change
    lane_img = np.copy(img)

    # find the edges
    canny_img = Canny.canny(lane_img)

    # det the region of intrest
    masked_img = Region_of_intrest.roi(canny_img)

    # draw lines on masked img
    lines = cv2.HoughLinesP(masked_img, 2, np.pi/180,
                            90, np.array([]), minLineLength=8, maxLineGap=10)

    # average lines
    avr_lines = Combin_Lines.average_line(masked_img, lines)
    line_img = Display_lines.display_lines(lane_img, avr_lines)

    # add the lines and the img
    final_img = cv2.addWeighted(lane_img, 0.7, line_img, 0.5, 2)

    ################################################
    # display video or camera
    ################################################
    cv2.imshow('result', final_img)
    if cv2.waitKey(5) == ord('q'):
        cap.release()
        cv2.destroyAllWindows()
        break
