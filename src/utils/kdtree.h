#ifndef __UTILS_KDTREE_H__
#define __UTILS_KDTREE_H__
/*
 * Object for quickly constructing and querying a kdtree
 */

namespace rearview {

//template<size_t Nd>
class Hyperrect
{
    typedef const double* pt_t;
  public:
    Hyperrect () {}
    ~Hyperrect () {}

  private:
    pt_t _min, _max;
};


template<size_t Nd>
class Kdtree_node
{
  public:
    Kdtree_node () {}
    ~Kdtree_node () {}

  private:
    //Hyperrect<Nd> _rect;
    Kdtree_node *_left, *_right;
};


template<size_t Nd>
class Kdtree
{
  public:
    Kdtree () {}
    ~Kdtree () {}

  private:
    //Kdtree_node _root;
};

} // rearview

#endif // __UTILS_KDTREE_H__
