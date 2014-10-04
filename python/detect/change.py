#!/usr/bin/env python
import sys

import cv2
import numpy as np
import matplotlib.pyplot as plt

#cap = cv2.VideoCapture (0)
#
#im0 = None
#while True:
#    ret, im = cap.read ()
#    blur = cv2.GaussianBlur (im, (0,0), 5)
#    if not im0 is None:
#        cv2.imshow ('Testing 1, 2, 3...', blur-im0)
#    im0 = blur
#    print im0.shape
#
#    key = cv2.waitKey (10)
#    if key > 0: break

im0 = cv2.imread (sys.argv[1], cv2.CV_LOAD_IMAGE_GRAYSCALE)
im1 = cv2.imread (sys.argv[2], cv2.CV_LOAD_IMAGE_GRAYSCALE)

#diff = np.abs ((im0-im0.mean ())-(im1-im1.mean ()))
diff = np.abs (im0-im1)
diff[diff < 100] = 0
diff[diff >= 100] = 255

fig = plt.figure (figsize=(15,5))
ax0 = fig.add_subplot (131)
ax1 = fig.add_subplot (132)
ax2 = fig.add_subplot (133)

ax0.axis ('off')
ax0.set_title ('im0')

ax1.axis ('off')
ax1.set_title ('im1')

ax2.axis ('off')
ax2.set_title ('diff')

ax0.imshow (im0, plt.cm.gray)
ax1.imshow (im1, plt.cm.gray)
ax2.imshow (diff)

plt.tight_layout ()
plt.show ()
