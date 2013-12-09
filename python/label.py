#!/usr/bin/env python
import sys

import numpy as np
from scipy.spatial.distance import cdist
from cv2 import imwrite

import matplotlib.pyplot as plt
#import pydot

import cPickle as pickle

def read_images (fname):
    try:
        f = open (fname, 'r')
    except Exception as err:
        print 'Error opening file: %s' % err
        sys.exit (0)

    imgs = []
    for ii,l in enumerate (f):
        im = np.fromstring (l,sep='\t')
        #imwrite ('imgs/img%03d.png'%ii, im.reshape (24,24))
        imgs.append (im/im.max ())
    f.close ()
    return imgs

def label_images (imgs):
    labels = []
    for im in imgs:
        fig = plt.figure ()
        ax = fig.add_subplot (111)
        ax.imshow (im.reshape (24,24))
        plt.show ()
        label = raw_input ('enter label: ')
        labels.append (label)
    with open ('labels.pkl', 'wb') as f:
        pickle.dump (labels, f)
    return labels

if __name__ == '__main__':
    if len (sys.argv) < 2:
        print 'usage: %s <unlabeled.txt>' % sys.argv[0]
        sys.exit (0)
    
    imgs = read_images (sys.argv[1])
    n = len (imgs)

    if len (sys.argv) > 2:
        with open (sys.argv[2], 'rb') as f:
            labels = pickle.load (f)
    else:
        labels = label_images (imgs)

    # compute inter image distances
    imgs = np.asarray (imgs)
    dx = cdist (imgs,imgs)
    print 'min/max/mean distances : ', dx.min (), dx.max (), dx.mean ()

    ## pydot
    #print 'pydotting'
    #T = 8
    #g = pydot.Dot (graph_type='graph')
    ##node = {i: pydot.Node (str (i),fontcolor='transparent',shape='rectangle',image='imgs/img%03d.png'%i) for i in range (n)}
    #node = {i: pydot.Node (str (i),shape='rectangle') for i in range (n)}
    #for i in range (n):
    #    for j in range (i+1,n):
    #        if dx[i,j] < 4:
    #            g.add_edge (pydot.Edge (node[i],node[j]))
    #g.write_png ('faces.png',prog='dot')

    # plot everything
    print 'plotting'
    fig1 = plt.figure (1)
    ax1 = fig1.add_subplot (111)
    ax1.imshow (dx,interpolation='nearest')
    fig1.tight_layout ()

    fig2 = plt.figure (2)
    rows,cols = np.ceil (n/10.), 10.
    for ii,im in enumerate (imgs):
        ax = fig2.add_subplot (rows,cols,ii)
        ax.imshow (im.reshape (24,24), cmap=plt.cm.gray)
        ax.axis ('off')
    fig2.tight_layout ()

    plt.show ()
    sys.exit (0)
