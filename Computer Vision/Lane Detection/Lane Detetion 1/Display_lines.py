import numpy as np
import cv2
def display_lines(img, lines):
    line_img= np.zeros_like(img)
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line.reshape(4)
            cv2.line(line_img, (x1, y1), (x2, y2), (0, 0, 255),11)
    else:
         line_img= np.zeros_like(img)
    return line_img
                                            