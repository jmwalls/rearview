#ifndef __UTILS_CELLNN_H__
#define __UTILS_CELLNN_H__
/*
 * Object for quickly computing fixed radius nearest neighbors with a
 * Euclidean distance metric using a cell-based implementation. Each point is
 * hashed into a hypercube. Point lookups just involve finding the cube (and
 * surrounding cubes) of the query point.
 *
 * Refer to :
 * - A survey of techniques for fixed radius near neighbor searching
 *   Bentley, 1975
 * - Ryan Wolcott's grid_3d/point_bucket implementation
 *
 */

#include <stdint.h>
#include <assert.h>

#include <cmath>
#include <bitset>
#include <list>
#include <map>
#include <string>
#include <vector>

namespace rearview {

/* Bitset compare
 *
 * Nb : number of bits
 */
template<size_t Nb>
struct Bitset_compare
{
    bool operator() (const std::bitset<Nb>& lhs, const std::bitset<Nb>& rhs) const
    {
        for (size_t ii=Nb;ii>0;--ii) {
            size_t i = ii-1;
            if (lhs[i] < rhs[i]) return true;
            else if (lhs[i] > rhs[i]) return false;
        }
        return false;
    }
};


/* Cell-based fixed radius nearest neighbor search
 *
 * Nd : dimension of space
 * Nb : number of bits per dimension including sign bit (64bits maximum)
 */
template<size_t Nd, size_t Nb>
class Cell_nn
{
    typedef std::list<const double*> cell_t;
    typedef typename std::map<std::bitset<Nd*Nb>, cell_t, Bitset_compare<Nd*Nb>>::const_iterator cell_iterator;

    typedef std::pair<double,const double*> distpt_t;
  public:
    Cell_nn () 
    {
        for (size_t i=0;i<Nd;++i) _size[i] = 1.;
        init_bits ();
    }
    Cell_nn (const double* s) 
    {
        for (size_t i=0;i<Nd;++i) _size[i] = s[i];
        init_bits ();
    }
    ~Cell_nn () {}


    /*
     * access list of points in same cell as p
     */
    cell_t& operator() (const double* p) {return _cells[hash (p)];}

    /*
     * add point p to appropriate cell
     */
    void add_point (const double* p) {_cells[hash (p)].push_back (p);}

    /*
     * compute fixed radius nearest neighbor search
     * idea is to perform a brute force search over all (adjacent) cells that
     * could potentially hold points within radius.
     */
    std::list<distpt_t> near (const double* p, double radius);

    /*
     * for debugging---access all cells in _cells
     */
    cell_iterator cells_begin () {return _cells.cbegin ();}
    cell_iterator cells_end () {return _cells.cend ();}

  private:
    std::map<std::bitset<Nd*Nb>, cell_t, Bitset_compare<Nd*Nb>> _cells;
    double _size[Nd];    // grid cell size
    int64_t _widthmask;

    std::bitset<Nd*Nb> hash (const double* p)
    {
        std::bitset<Nd*Nb> h, hi;
        for (size_t i=0;i<Nd;++i) {
            hi.reset ();
            int64_t c = fabs (p[i]/_size[i]);
            assert (c == (c & _widthmask)); // should not overflow cells
            hi |= ((p[i]<0) << (Nb-1)) | c; // include sign bit
            h |= (hi << ((Nd-(i+1))*Nb));
        }
        return h;
    }

    void init_bits ()
    {
        assert (Nb < 64);
        for (size_t i=0;i<Nb-1;++i) _widthmask = (_widthmask << 1) | 1;
    }
};

template<size_t Nd, size_t Nb>
std::list<std::pair<double,const double*> > 
Cell_nn<Nd,Nb>::near (const double* p, double radius)
{
    std::list<distpt_t> pts;

    std::vector<int> to_check (Nd), delta (Nd);
    for (size_t i=0;i<Nd;++i) {
        to_check[i] = ceil (radius/_size[i]);
        delta[i] = -to_check[i];
    }

    std::vector<double> nbr (Nd);
    auto itd = delta.begin (), itc = to_check.begin ();
    while (true) {
        for (size_t i=0;i<Nd;++i) nbr[i] = p[i] + delta[i]*_size[i];
        cell_t cnbr = _cells[hash (nbr.data ())];
        for (auto& pnbr : cnbr) {
            double d = 0;
            for (size_t i=0;i<Nd;++i) d += pow (p[i] - pnbr[i],2);
            if (d < radius*radius) pts.push_back (std::make_pair (sqrt (d), pnbr));
        }
        
        if (++(*itd) > *itc) { // increment indicator iterators
            *itd = -*itc;
            while (true) {
                ++itd,++itc;
                if (itd==delta.end ()) break;
                if (++(*itd) > *itc) *itd = -*itc;
                else break;
            }
            if (itd==delta.end ()) break;
            else itd = delta.begin (), itc = to_check.begin ();
        }
    }

    pts.sort ();
    return pts;
}

} // rearview

#endif // __UTILS_CELLNN_H__
