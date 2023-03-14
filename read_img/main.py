import cv2
 
# Image Read
img = cv2.imread('../img/freya.png')

# Image Show
cv2.imshow('freya', img)

cv2.waitKey(0)
cv2.destroyAllWindows()
