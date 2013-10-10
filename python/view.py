#!/usr/bin/env python
import cv2

cap = cv2.VideoCapture (0)

while True:
    ret, im = cap.read ()
    cv2.imshow ('Testing 1, 2, 3...', im)
    key = cv2.waitKey (10)
    if key > 0: break

cv2.imwrite ('test.png', im)
