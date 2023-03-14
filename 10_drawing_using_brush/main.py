import cv2
import numpy

def draw_rectangle(event,x,y,flags,param):
    if event == cv2.EVENT_LBUTTONDBLCLK:
        cv2.rectangle(frame,(x,y),(x+10,y+10), (255,0,0), -1)

frame = numpy.zeros((256,256,3), numpy.uint8)
cv2.namedWindow('frame')
cv2.setMouseCallback('frame', draw_rectangle)

while (True):
    cv2.imshow('frame', frame)
    if cv2.waitKey(20) == ord('q'):
        break

cv2.destroyAllWindows()
