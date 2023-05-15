#pragma once


namespace ariel
{
    class Point
    {
    private:
        
        double _x, _y;

    public:

        //constructors:
        Point(double x, double y);
        ~Point();

        //functions to implement:
        double distance(Point other);  //sqrt((x1-x2)^2 +(y1-y2)^2)
        void print();
        static Point moveTowards(Point origin, Point destination, double distance);

        //my added functions:
        double getX();
        double getY();

    };
    

}; // namespace ariel


