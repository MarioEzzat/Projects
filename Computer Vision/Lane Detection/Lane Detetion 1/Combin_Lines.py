import numpy as np

def make_coordinates(img, line_parameters):
	slope, intercept = line_parameters
	y1 = img.shape[0]
	y2 = int(y1*(3.2/5.0))
	x1 = int((y1 - intercept)/slope)
	x2 = int((y2 - intercept)/slope)
	return np.array([x1, y1, x2, y2])


class static:
	left_fit = []
	right_fit = []
def average_line(img,lines):
	if lines is not None:
		for line in lines:
			x1, y1, x2, y2 = line.reshape(4)
			if x1 == x2:
				return lines
			parameters = np.polyfit((x1, x2), (y1, y2), 1)
			slope = parameters[0]
			intercept = parameters[1]
			if slope < 0:
				static.left_fit.append((slope,intercept))
			elif slope > 0:
				static.right_fit.append((slope, intercept))
			
		left_fit_average = np.average(static.left_fit, axis=0)
		right_fit_average = np.average(static.right_fit, axis=0)
		left_line = make_coordinates(img, left_fit_average)
		right_line = make_coordinates(img, right_fit_average)
	return np.array([left_line,right_line])
