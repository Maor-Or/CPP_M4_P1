#pragma once
#include "Point.hpp"
//#include <string>
namespace ariel
{
    class Character
    {
    protected:
        Point _location;
        int _hitPoints;
        std::string _name;

    public:
        Character(std::string name, Point characterLoction);
        ~Character();
    
    // functions to implement:
    bool isAlive() const;
    double distance(Character *p_other) const;
    void hit(int dmg);
    std::string getName() const;
    Point getLocation() const;
    virtual std::string print()const;

    //my added functions:
    
    };
} // namespace ariel
