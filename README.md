##Rearview mirror
--------

Rearview mirror detects familiar faces walking into the camera field of
vision.

###Build
-----
To build:

$ mkdir build  
$ cd build  
$ cmake ..  
$ make  

###TODO
-----

Cluster (e.g., by Gaussian mixture models), user provides semantic
labels.

See variational Dirichlet process (VDP) for learning the GMM (does not require
a prior on the number of clusters). Other clustering algorithms such as
density-based spatial clustering of applications with noise (DBSCAN) may also
be appropriate.


###Authors
-----
Jeff Walls <jmwalls@umich.edu>
