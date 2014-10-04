#!/usr/bin/env python
import sys

import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    pts = np.loadtxt (sys.argv[1])
    ids = pts[:,0]
    xy = pts[:,1:]

    nn = np.loadtxt (sys.argv[2])

    fig = plt.figure ()
    ax = fig.add_subplot (111)

    ax.scatter (xy[:,0],xy[:,1],c=ids,cmap=plt.cm.jet, edgecolor='none')
    ax.plot (nn[:,0],nn[:,1], 'k.')

    #uids = np.unique (ids)
    #for uid in uids:
    #    ii = np.where (ids==uid)[0]
    #    x,y = xy[ii,0], xy[ii,1]
    #    xm,ym = x.mean (), y.mean ()
    #    ax.text (xm,ym,str (int (uid)))
    #ax.axis ([xy[:,0].min (),xy[:,0].max (),
    #    xy[:,1].min (),xy[:,1].max ()])

    ax.axis ('equal')

    plt.show ()

    sys.exit (0)
