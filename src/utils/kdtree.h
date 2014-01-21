#ifndef __UTILS_KDTREE_H__
#define __UTILS_KDTREE_H__
/*
 * Object for quickly constructing and querying a kdtree
 */

namespace rearview {

//class Hyperrect
//{
//  public:
//    Hyperrect (const double* min, const double* max) 
//        : _min (min), _max (max) {}
//    ~Hyperrect () {}
//
//  private:
//    const double *_min, *_max;
//
//    Hyperrect () {}
//};


template<size_t Nd>
class Kdtree_node
{
  public:
    Kdtree_node () {}
    ~Kdtree_node () {}

  private:
    const double* _pos;
    size_t _dir;

    Kdtree_node *_left, *_right;
};


/*
 * T : container type with iterators to loop over points
 */
template<class T, size_t Nd>
class Kdtree
{
  public:
    Kdtree (const T& points) {}
    ~Kdtree () {}

  private:
    Kdtree_node<Nd>* _root;

    Kdtree () {}
};

} // rearview

#endif // __UTILS_KDTREE_H__
