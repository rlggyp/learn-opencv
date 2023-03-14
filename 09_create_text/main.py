import cv2
import numpy

frame = numpy.zeros((256,256,3), numpy.uint8)
font = cv2.FONT_HERSHEY_SIMPLEX
frame = cv2.putText(frame, 'Freya', (42,140), font, 2, (0,0,255), 1)

cv2.imshow('text', frame)
cv2.waitKey(0)
cv2.destroyAllWindows()
