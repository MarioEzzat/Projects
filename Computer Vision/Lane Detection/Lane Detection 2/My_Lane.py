'''
Lane Detection 2
Author: Mario Ezzat
'''
import cv2
import numpy as np


class static:
    left_fit = []
    right_fit = []


def canny(img):
    # change img to gray
    gray_img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    # high quality
    blur = cv2.GaussianBlur(gray_img, (5, 5), 0)
    # make the edges white lines
    canny = cv2.Canny(blur, 25, 120)
    return canny


def roi(img):
    # draw rectangle shape white pixles
    hight = img.shape[0]
    triangle = np.asarray([[(300, hight), (1100, hight), (500, 200)]])
    # black img with same size of my img
    mask = np.zeros_like(img)
    cv2.fillPoly(mask, triangle, 250)
    masked_img = cv2.bitwise_and(img, mask)
    return masked_img


def make_coordinates(img, line_parameters):
    slope, intercept = line_parameters
    y1 = img.shape[0]
    y2 = int(y1*(3/5))
    x1 = int((y1 - intercept)/slope)
    x2 = int((y2 - intercept)/slope)
    return np.array([x1, y1, x2, y2])


def average_line(img, lines):
    for line in lines:
        x1, y1, x2, y2 = line.reshape(4)
        parameters = np.polyfit((x1, x2), (y1, y2), 1)
        slope = parameters[0]
        intercept = parameters[1]
        if slope < 0:
            static.left_fit.append((slope, intercept))
        elif slope > 0:
            static.right_fit.append((slope, intercept))
    left_fit_average = np.average(static.left_fit, axis=0)
    right_fit_average = np.average(static.right_fit, axis=0)
    left_line = make_coordinates(img, left_fit_average)
    right_line = make_coordinates(img, right_fit_average)
    return np.array([left_line, right_line])


def display_lines(img, lines):
    line_img = np.zeros_like(img)
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line.reshape(4)
            cv2.line(line_img, (x1, y1), (x2, y2), (0, 255, 0), 10)
    return line_img


#my_img = cv2.imread('img.png')
cap = cv2.VideoCapture("street.mp4")
while (True):
    _, frame = cap.read()
    frame = cv2.resize(frame, None, fx=0.9, fy=0.9)
    # copy the img to make change
    lane_img = np.copy(frame)

    # find the edges
    canny_img = canny(lane_img)

    # det the region of intrest
    masked_img = roi(canny_img)

    # draw lines on masked img
    lines = cv2.HoughLinesP(masked_img, 2, np.pi/180,
                            60, np.array([]), minLineLength=40, maxLineGap=5)

    # average lines
    avr_lines = average_line(lane_img, lines)
    line_img = display_lines(lane_img, avr_lines)

    # add the lines and the img
    add_img = cv2.addWeighted(lane_img, 0.8, line_img, 1, 1)
    
    # show the result
    cv2.imshow('res', add_img)
    if cv2.waitKey(1) == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()    

