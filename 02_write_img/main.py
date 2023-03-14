import cv2
 
# Image Read
img = cv2.imread('../img/freya.png')

# Image Show
cv2.imshow('freya', img)

# Image Write
cv2.imwrite('new_freya.png', img)

cv2.waitKey(0)
cv2.destroyAllWindows()
