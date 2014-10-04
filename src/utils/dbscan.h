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
 * dimensions D in the data set, as minpts>=D+1.  The low value of minpts=1
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

#include <algorithm>
#include <list>

#include "cellnn.h"

namespace rearview {

/* DBSCAN clustering object
 *
 * Nd : dimension of space
 * Nb : number of bits per dimension including sign bit (64bits maximum)
 */
template<size_t Nd, size_t Nb>
class DBSCAN
{
    typedef const double* pt_t;
    typedef std::list<pt_t> pts_t;

    typedef std::pair<double,const double*> distpt_t;

    typedef std::list<pts_t>::const_iterator cluster_iterator;
  public:
    DBSCAN (double eps, size_t min_pts) 
        : _eps (eps), _min_pts (min_pts), _nnbrs () {}
    ~DBSCAN () {}

    void add_point (const double* p) 
    {
        _points.push_back (p);
        _nnbrs.add_point (p);
    }

    /*
     * batch clustering procedure
     */
    void cluster () 
    {
        _clusters.clear ();

        pts_t unvisited = _points, clustered;
        while (!unvisited.empty ()) {
            pt_t p = unvisited.front ();
            unvisited.pop_front ();

            std::list<distpt_t> nbrs = _nnbrs.near (p, _eps);
            if (nbrs.size () < _min_pts) // p is noise
                continue; 
            else {                       // expand cluster
                pts_t nbrpts;
                for (auto& n : nbrs) nbrpts.push_back (n.second);
                expand_cluster (p, nbrpts, unvisited, clustered);
            }
        }
    }

    /* 
     * access clusters
     */
    cluster_iterator clusters_begin () {return _clusters.cbegin ();}
    cluster_iterator clusters_end () {return _clusters.cend ();}

  private:
    double _eps;
    size_t _min_pts;

    pts_t _points;
    std::list<pts_t> _clusters;

    Cell_nn<Nd,Nb> _nnbrs;

    void expand_cluster (const pt_t& p, pts_t& nbrs, pts_t& unvisited, pts_t& clustered)
    {
        pts_t cluster;
        cluster.push_back (p);
        clustered.push_back (p);

        while (!nbrs.empty ()) {
            pt_t pp = nbrs.front ();
            nbrs.pop_front ();

            auto it = std::find (unvisited.begin (), unvisited.end (), pp);
            if (it!=unvisited.end ()) { // pp is unvisited
                unvisited.erase (it);
                std::list<distpt_t> pnbrs = _nnbrs.near (pp, _eps);
                if (pnbrs.size () >= _min_pts) {
                    for (auto& n : pnbrs) nbrs.push_back (n.second);
                }
            }
            it = std::find (clustered.begin (), clustered.end (), pp);
            if (it==clustered.end ()) { // pp not clustered already
                clustered.push_back (pp);
                cluster.push_back (pp);
            }
        }
        _clusters.push_back (cluster);
    }

    DBSCAN () {}
};

} // rearview

#endif // __UTILS_DBSCAN_H__
