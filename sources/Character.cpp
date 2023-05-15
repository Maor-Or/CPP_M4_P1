#pragma once

#include "Character.hpp"
#include <string>
#include <iostream>

using namespace std;

namespace ariel
{
    // constructors:
    // Character::Character(string name, Point characterLoction){}

    Character::Character(string name, Point characterLoction)
        : _name(name), _location(characterLoction), _hitPoints(100)
    {
    }

    Character::~Character()
    {
    }

    // functions to implement:
    bool Character::isAlive() const { return _hitPoints > 0; }
    double Character::distance(Character *p_other) const
    {
        return this->getLocation().distance(p_other->getLocation());
    }
    void Character::hit(int dmg) { _hitPoints -= dmg; }
    string Character::getName() const { return _name; }
    Point Character::getLocation() const { return _location; }
    void Character::print() const
    {
        if (isAlive())
        {
            cout << "C/N";
        }
    }

    // my added functions:

}; // namespace ariel
