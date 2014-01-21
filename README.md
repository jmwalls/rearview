##Rearview mirror
--------

Rearview mirror detects familiar faces walking into the camera field of
view.

`utils` provides some interesting methods for playing around with clustering
and nearest neighbors. Included for computing nearest neighbors (nearest or
fixed-radius) are

* linear : `Linear_nn`
* cell : `Cell_nn`
* kd-tree : `Kd_tree`
* FLANN : wrapper around FLANN for approximate nearest neighbors.


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
