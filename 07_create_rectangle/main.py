import cv2
import numpy

frame = numpy.zeros((256,256,3), numpy.uint8)
frame = cv2.rectangle(frame, (63,63), (191,191), (0,0,255), -1)

cv2.imshow('rectangle', frame)
cv2.waitKey(0)
cv2.destroyAllWindows()
