##Rearview mirror
--------

Rearview mirror detects familiar faces walking into the camera field of view.
Basic idea is to match a query image into a database (representation?). Tough
to accomplish because we need to deal with pose variance, and non-rigid
expressions.

Pipeline:

1. Detect (and align?)
2. Build feature vector (spatial pyramid, Fisher vectors, ...) from
   affine-invariant (engineered) descriptors.
3. Apply some dimensionality reduction scheme (possibly learned from training
   data---metric/similarity learning).
4. Match to database image (k-NN?).
5. Update database? (Probably later, offline)

Face recognition:

    * Taigman, CVPR 2014
    * Guillaumin et al. `Is that you? Metric learning approaches for face
      identification', ICCV 2009
    * Lue et al., `Neighborhood repulsed metric learning for kinship
      verification', CVPR 2012

Metric learning:
    
    * Davis, ICML 2007
    * Weinberger, NIPS 2006

Back propagation:

    * Rumelhart, Nature 1986
    * LeCun, IEEE 1998


`mlearn` implements a few metric learning algorithms.

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

Can we use something like Cao (2013) to match into different regions of a
graph for more efficient look up?

For offline labeling, might want to cluster first, then the user can label
clusters as opposed to individual instances. Cluster (e.g., by Gaussian
mixture models), user provides semantic labels.

See variational Dirichlet process (VDP) for learning the GMM (does not require
a prior on the number of clusters). Other clustering algorithms such as
density-based spatial clustering of applications with noise (DBSCAN) may also
be appropriate.

__IDEA:__ Just perform PCA over the 24x24 normalized images (raw feature
vector), and cluster in this reduced space (4 or 5 dimensions). Could also
think about applying locally linear embedding (LLE) instead of PCA. See
\cite{Turk1991} and \cite{Belhumeur1997} for PCA. See \cite{deRitter2002} and
\cite{Vanderplas2009} for discussion of LLE and classification.


###Authors
-----
Jeff Walls <jmwalls@umich.edu>
