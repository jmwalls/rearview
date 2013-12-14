#ifndef __UTILS_POINT_H__
#define __UTILS_POINT_H__

#include <algorithm>

namespace rearview {

template<class T, size_t Nd>
class Point
{
  public:
    Point () : _x (new T[Nd]) {for (size_t i=0;i<Nd;++i) _x[i] = 0;}
    explicit Point (T* x) : _x (new T[Nd]) {std::copy (x,x+Nd,_x);}
    Point (const Point& p) : _x (new T[Nd]) {std::copy (p._x,p._x+Nd,_x);}
    ~Point () {delete _x;}

    Point& operator= (const Point &p)
    {
        if (_x) delete[] _x;
        _x = new T[Nd];
        std::copy (p._x,p._x+Nd,_x);
        return *this;
    }

    bool operator== (const Point& p) const
    {
        for (size_t i=0;i<Nd;++i) 
            if (_x[i] != p._x[i]) return false;
        return true;
    }

  private:
    T* _x;
};

} // rearview

#endif // __UTILS_POINT_H__
