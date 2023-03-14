import cv2
import numpy

frame = numpy.zeros((256,256,3), numpy.uint8)
frame = cv2.circle(frame, (127,127), 40, (0,0,255), -1)

cv2.imshow('circle', frame)
cv2.waitKey(0)
cv2.destroyAllWindows()
