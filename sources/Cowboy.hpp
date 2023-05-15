#pragma once

#include "Character.hpp"
#include <string>

#define BULLETAMOUNT 6
#define COWBOY_HP 110

namespace ariel
{
    class Cowboy : public Character
    {
    private:
        int _bulletAmount;

    public:
    
    //constructors:
        Cowboy(std::string name, Point characterLoction);
        ~Cowboy();
    
    //functions to implement:
    void shoot(Character *enemy) const;
    bool hasboolets() const;
    void reload();


    };    
} // namespace ariel
