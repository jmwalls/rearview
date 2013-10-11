#!/usr/bin/env python
import sys

import numpy as np
from scipy.spatial.distance import cdist
import matplotlib.pyplot as plt

if __name__ == '__main__':
    if len (sys.argv) < 2:
        print 'usage: %s <unlabeled.txt>' % sys.argv[0]
        sys.exit (0)
    
    try:
        f = open (sys.argv[1], 'r')
    except Exception as err:
        print 'Error opening file: %s' % err
        sys.exit (0)

    imgs = []
    for ii,l in enumerate (f):
        imgs.append (np.fromstring (l,sep='\t'))
    f.close ()

    imgs = np.asarray (imgs)
    dx = cdist (imgs,imgs)

    fig1 = plt.figure (1)
    ax1 = fig1.add_subplot (111)
    ax1.imshow (dx,interpolation='nearest')
    fig1.tight_layout ()

    fig2 = plt.figure (2)
    n = len (imgs)
    rows,cols = np.ceil (n/10.), 10.
    for ii,im in enumerate (imgs):
        ax = fig2.add_subplot (rows,cols,ii)
        ax.imshow (im.reshape (24,24), cmap=plt.cm.gray)
        #ax.set_title (str (ii))
        ax.axis ('off')
    fig2.tight_layout ()

    plt.show ()
    sys.exit (0)
