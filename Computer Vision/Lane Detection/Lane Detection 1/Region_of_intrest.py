import numpy as np
import cv2
def roi(img):
	#draw rectangle shape white pixles
	hight = img.shape[0]
	triangle =np.array([[(120, hight), (955, hight), (530,300),(450,300)]])


	#black img with same size of my img
	mask = np.zeros_like(img)
	cv2.fillPoly(mask,triangle,(255, 255, 255) )
	masked_img = cv2.bitwise_and(img, mask)
	return masked_img
