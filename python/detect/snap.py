#!/usr/bin/env python
import cv2

cap = cv2.VideoCapture (0)

imcount = 0
while True:
    ret, im = cap.read ()
    cv2.imshow ('Snap image', im)
    key = cv2.waitKey (10)
    if key == 27 or key == 1048603: 
        print 'goodbye'
        break
    elif key > 0:
        print 'snapping image %d' % imcount
        cv2.imwrite ('test%03d.png'%imcount, im)
        imcount += 1
