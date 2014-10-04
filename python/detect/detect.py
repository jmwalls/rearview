#!/usr/bin/env python
import sys
import cv2

cascade = cv2.CascadeClassifier ('haarcascade_frontalface_alt.xml')

im = cv2.imread ('test.png')
rects = cascade.detectMultiScale (im)
if not len (rects):
    print 'no faces detected'
    sys.exit (0)

rects[:,2:] += rects[:,:2] 

for x1, y1, x2, y2 in rects: 
    cv2.rectangle(im, (x1, y1), (x2, y2), (127, 255, 0), 2) 

cv2.imwrite ('detect.png', im)
cv2.imshow ('Testing 1, 2, 3...', im)
while True:
    key = cv2.waitKey (10)
    if key > 0: break
