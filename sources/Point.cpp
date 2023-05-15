#include <iostream>
#include "Point.hpp"
#include <math.h>

namespace ariel
{

    // constructors:
    Point::Point(double x, double y) : _x(x), _y(y)
    {
    }

    Point::~Point()
    {
    }

    // functions to implement:
    double Point::distance(Point other)
    {
        return sqrt( pow((_x - other.getX()) , 2)  +  pow((_y - other.getY()) , 2) );
    }
    void Point::print(){std::cout << "("<<_x <<","<< _y<<")";}
    //TODO: implement this func:
    Point Point::moveTowards(Point origin, Point destination, double distance)
    {
        return{1,1};
    }

    // my added functions:
    double Point::getX(){return _x;}
    double Point::getY(){return _y;}
};
