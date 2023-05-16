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
        return sqrt(pow((_x - other.getX()), 2) + pow((_y - other.getY()), 2));
    }
    void Point::print() { std::cout << "(" << _x << "," << _y << ")"; }
    // TODO: implement this func:
    Point Point::moveTowards(Point origin, Point destination, double distance)
    {
        if (distance<0)
        {
        throw std::invalid_argument("Invalid argument: value must be non-negative");
        }
        
        
        double currDistance = origin.distance(destination);
        
        if (distance==0||currDistance == 0)
        {
            return origin;
        }

        if (currDistance <= distance)
        {
            return destination;
        }

        double ratio = distance / currDistance;

        double new_x_location =
            origin.getX() + (destination.getX() - origin.getX()) * ratio;

        double new_y_location =
            origin.getY() + (destination.getY() - origin.getY()) * ratio;

        // Point p_res(new_x_location, new_y_location);
        // return p_res;
        return{new_x_location,new_y_location};
    }

    // my added functions:
    double Point::getX() { return _x; }
    double Point::getY() { return _y; }
};
