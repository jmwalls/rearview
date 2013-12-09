#ifndef __UTILS_FIXEDRADNN_H__
#define __UTILS_FIXEDRADNN_H__
/*
 * object for quickly computing fixed radius nearest neighbors with a
 * Euclidean distance metric using a cell-based implementation.
 *
 * Each point is hashed into a hypercube. Point lookups just involve find the
 * cube (and surrounding cubes) of the query point.
 */

#include <stdint.h>
#include <assert.h>

#include <iostream>

#include <cmath>
#include <bitset>
#include <list>
#include <map>
#include <string>

/* Bitset compare
 *
 * Nb : number of bits
 */
template<size_t Nb>
struct Bitset_compare
{
    bool operator() (const std::bitset<Nb>& b0, const std::bitset<Nb>& b1) const
    {
        //for (size_t i=0;i<Nb;++i)
        //    if (b0[i] < b1[i]) return true;
        //return false;
        return b0.to_ulong () < b1.to_ulong ();
    }
};


/* Cell-based fixed radius nearest neighbor search
 *
 * Nd : dimension of space
 * Nb : number of bits per dimension (64bits maximum per dimension including
 * sign bit)
 */
template<size_t Nd, size_t Nb>
class Cell_nn
{
    typedef std::list<double*> cell_t;
    typedef typename std::map<std::bitset<Nd*Nb>, cell_t, Bitset_compare<Nd*Nb>>::const_iterator citerator;
  public:
    Cell_nn () 
    {
        for (size_t i=0;i<Nd;++i) _size[i] = 1.;
        for (size_t i=0;i<Nb;++i) _widthmask = (_widthmask << 1) | 1;
    }
    Cell_nn (const double* s) 
    {
        for (size_t i=0;i<Nd;++i) _size[i] = s[i];
        for (size_t i=0;i<Nb;++i) _widthmask = (_widthmask << 1) | 1;
    }
    ~Cell_nn () {}

    /*
     * access list of points in same cell as p
     */
    cell_t& operator() (double* p) {return _cells[hash (p)];}

    /*
     * add point p to appropriate cell
     */
    void add_point (double* p) 
    {
        _cells[hash (p)].push_back (p);
    }

    /*
     * for debugging---access all cells in _cells
     */
    citerator cells_begin () {return _cells.cbegin ();}
    citerator cells_end () {return _cells.cend ();}

  private:
    std::map<std::bitset<Nd*Nb>, cell_t, Bitset_compare<Nd*Nb>> _cells;
    double _size[Nd];
    int64_t _widthmask;

    std::bitset<Nd*Nb> hash (double* p)
    {
        std::bitset<Nd*Nb> h, hi;
        for (size_t i=0;i<Nd;++i) {
            hi.reset ();
            int64_t c = fabs (p[i]/_size[i]);
            assert (c == (c & _widthmask));// should not overflow cells
            hi |= ((p[i]<0) << Nb) | c; // include sign bit
            h |= (hi << ((Nd-(i+1))*(Nb+1)));
        }
        return h;
    }
};

#endif // __UTILS_FIXEDRADNN_H__
