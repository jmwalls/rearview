#ifndef __UTILS_DBSCAN_H__
#define __UTILS_DBSCAN_H__
/*
 * Basic DBSCAN template library
 *
 * DBSCAN essentially assumes all clusters of similar densities. DBSCAN
 * relies on two parameters, minpts and eps. Wikipedia recommends the
 * following with regards to tuning these values:
 *
 * minpts: 
 * As a rule of thumb, a minimum minpts can be derived from the number of
 * dimensions D in the data set, as minpts≥D+1.  The low value of minpts=1
 * does not make sense, as then every point on its own will already be a
 * cluster. With minpts=2, the result will be the same as of hierarchical
 * clustering with the single link metric, with the dendrogram cut at height
 * eps (however, DBSCAN is substantially faster, because it does not compute
 * the full dendrogram and can use indexes).  However, larger values are
 * usually better for data sets with noise and will yield more significant
 * clusters.  The larger the data set, the lager the value of minpts should be
 * chosen.
 *
 * eps: 
 * The value for eps can then be chosen by using a k-distance graph, plotting
 * the distance to the k=minpts nearest neighbor. Good values of eps are where
 * this plot shows a strong bend: if eps is chosen too small, a large part of
 * the data will not be clustered; whereas for a too high value of eps,
 * clusters will merge and the majority of objects will be in the same
 * cluster.
 *
 * [Wikipedia article](http://en.wikipedia.org/wiki/DBSCAN)
 *
 */

#include "fixedradnn.h"

template<size_t dim>
class DBSCAN
{
  public:
    DBSCAN (double eps, size_t min_pts) {}
    ~DBSCAN () {}

  private:
    DBSCAN () {}
};

#endif // __UTILS_DBSCAN_H__
