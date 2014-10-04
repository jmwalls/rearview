#!/usr/bin/env python
import sys
import glob

import cv2

cascade = cv2.CascadeClassifier ('/home/jeff/code/rearview/data/haarcascade_frontalface_alt2.xml')

if __name__ == '__main__':
    imgs = glob.glob ('*.png')
    imgs.sort ()

    for f in imgs:
        im = cv2.imread (f)
        rects = cascade.detectMultiScale (im)

        if not len (rects):
            print 'no faces detected'
        else:
            rects[:,2:] += rects[:,:2] 
            for x1, y1, x2, y2 in rects: 
                cv2.rectangle(im, (x1, y1), (x2, y2), (127, 255, 0), 2) 

        #cv2.imwrite ('detect.png', im)
        cv2.imshow ('Testing 1, 2, 3...', im)
        while True:
            key = cv2.waitKey (10)
            if key > 0: break

    sys.exit (0)

