import cv2
import numpy

frame = numpy.zeros((256, 256, 3), numpy.uint8)
frame = cv2.line(frame, (0,0), (255,255), (0,0,255), 3)
frame = cv2.line(frame, (255,0), (0,255), (0,0,255), 3)

cv2.imshow('frame', frame)
cv2.waitKey(0)
cv2.destroyAllWindows()
