#ifndef POINT2D_H
#define POINT2D_H
#include <vector>
#include "SimplePoint2D.h"
#include <memory>
using namespace std;


class Point2D {
private:
    class Impl;
    Impl* pimpl;


public:
    Point2D();
    Point2D(vector<SimplePoint2D> _pointCollection);
    Point2D(Point2D const &sourcePoint2D);
    Point2D(Point2D &&sourcePoint2D);
    ~Point2D();

    class Iterator;
    Iterator begin();
    Iterator end();

};

class Point2D::Iterator
{
    class IterImpl;
    IterImpl* pimpl;
    
    public:
    Iterator(Impl* p, bool isBegin);
    const SimplePoint2D& operator*();
    Iterator& operator++();
    Iterator& operator++(int);
    bool operator==(const Point2D::Iterator& i);
    bool operator!=(const Point2D::Iterator& i);
};

#endif //POINT2D_H
