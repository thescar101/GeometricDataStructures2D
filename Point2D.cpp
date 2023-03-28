#include "Point2D.h"
#include <algorithm>
using namespace std;


struct Point2D::Impl
{
    Impl(){};

    Impl(vector<SimplePoint2D> _pointCollection): pointCollection(move(_pointCollection)){};

    vector<SimplePoint2D> pointCollection;
};

struct Point2D::Iterator::IterImpl
{
    Impl* pointsPTR;
    int currentIndex;
    IterImpl(Impl* p, bool isBegin);
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

Point2D::Iterator Point2D::begin()
{
    Iterator itr(this->pimpl, true);
    return itr;
}

Point2D::Iterator Point2D::end()
{
    Iterator itr(this->pimpl, false);
    return itr;
}

Point2D::Iterator::IterImpl::IterImpl(Impl* p, bool isBegin)
{
    pointsPTR = p;

    if (isBegin)
        currentIndex = 0;
    else
        currentIndex = pointsPTR->pointCollection.size();
}

Point2D::Iterator::Iterator(Impl* p, bool isBegin) : pimpl(new IterImpl(p, isBegin))
{
}

const SimplePoint2D& Point2D::Iterator::operator*()
{
    return pimpl->pointsPTR->pointCollection.at(pimpl->currentIndex);
}

Point2D::Iterator& Point2D::Iterator::operator++()
{
    pimpl->currentIndex++;
    return *this;
}

Point2D::Iterator& Point2D::Iterator::operator++(int)
{
    ++(*this);
    return *this;
}

bool Point2D::Iterator::operator==(const Point2D::Iterator& i)
{
    return this->pimpl->currentIndex == i.pimpl->currentIndex;
}

bool Point2D::Iterator::operator!=(const Point2D::Iterator& i)
{
    return !(*this == i);
}

