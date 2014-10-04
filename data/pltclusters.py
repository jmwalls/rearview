#!/usr/bin/env python
import sys

import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    pts = np.loadtxt (sys.argv[1])
    ids = pts[:,0]
    xy = pts[:,1:]

    fig = plt.figure ()
    ax = fig.add_subplot (111)

    ax.scatter (xy[:,0],xy[:,1],c=ids,cmap=plt.cm.jet, edgecolor='none')

    ax.axis ('equal')
    plt.show ()

    sys.exit (0)
