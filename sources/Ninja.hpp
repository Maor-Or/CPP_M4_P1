#pragma once

#include "Character.hpp"
#include <string>

namespace ariel
{
    class Ninja : public Character
    {
    protected:
        
        int _speed;

    public:

        //constructors:
        Ninja(std::string name, Point characterLoction);
        ~Ninja();
    
        //functions to implement:
        void move(const Character *enemy);
        void slash(Character *enemy) const;
        
    };
    
} // namespace ariel
