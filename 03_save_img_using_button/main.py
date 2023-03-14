import cv2

img = cv2.imread('../img/freya.png')

cv2.imshow('freya', img)

key = cv2.waitKey(0)

if key == ord('s'):
    cv2.imwrite('new_freya.png', img)
    print("Sucessfully saved...")

cv2.destroyAllWindows()
