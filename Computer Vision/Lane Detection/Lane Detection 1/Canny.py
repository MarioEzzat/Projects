import cv2
def canny(img):
	#change img to gray
	gray_img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
	#bulr img
	blur = cv2.GaussianBlur(gray_img, (5, 5), 0)
	#make the edges white lines
	canny_img = cv2.Canny(blur, 50, 160)
	return canny_img
