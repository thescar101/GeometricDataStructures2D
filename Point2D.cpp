#include "Point2D.h"
#include <algorithm>
using namespace std;


struct Point2D::Impl
{
    Impl(){};

    Impl(vector<SimplePoint2D> _pointCollection): pointCollection(move(_pointCollection)){};

    vector<SimplePoint2D> pointCollection;
};

class Point2D::Iterator::IterImpl
{
    friend Point2D;

    vector<SimplePoint2D>::iterator vectorIter;

    public:
    IterImpl();
    SimplePoint2D operator*();
    void operator++();
    bool operator==(const Point2D::Iterator& i);
    bool operator!=(const Point2D::Iterator& i);
};

Point2D::Point2D() {}

Point2D::Point2D(vector<SimplePoint2D> _pointCollection):pimpl(new Impl())
{
    _pointCollection.erase(unique(_pointCollection.begin(), _pointCollection.end()), _pointCollection.end());
    sort(_pointCollection.begin(), _pointCollection.end());
    this->pimpl->pointCollection = _pointCollection;
}
Point2D::Point2D(Point2D const &sourcePoint2D): pimpl(new Impl(*sourcePoint2D.pimpl))
{
}
Point2D::Point2D(Point2D &&sourcePoint2D)
{
    this->pimpl = move(sourcePoint2D.pimpl);
    sourcePoint2D.pimpl = nullptr;
}

Point2D::~Point2D(){}


Point2D::Iterator::IterImpl::IterImpl() {}

SimplePoint2D Point2D::Iterator::IterImpl::operator*()
{
    return *vectorIter;
}
void Point2D::Iterator::IterImpl::operator++()
{
    vectorIter++;
}
bool Point2D::Iterator::IterImpl::operator==(const Point2D::Iterator& i)
{
    return (this->vectorIter == i.vectorIter);
}
bool Point2D::Iterator::IterImpl::operator!=(const Point2D::Iterator& i)
{
    return !(*this == i);
}

Point2D::Iterator Point2D::begin() 
{
    Iterator returnIter; // Construct an iter to return
    returnIter.vectorIter = this->pimpl->pointCollection.begin(); // Set state to beginning of point collection
    return returnIter;
}

Point2D::Iterator Point2D::end() 
{
    Iterator returnIter; // Construct an iter to return
    returnIter.vectorIter = this->pimpl->pointCollection.end(); // Set state to end of point collection
    return returnIter;
}