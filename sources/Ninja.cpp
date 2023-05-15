#include "Ninja.hpp"
#include <string>

namespace ariel
{

        //constructors:
    Ninja::Ninja(std::string name, Point characterLoction)
        : Character(name, characterLoction)
    {
    }

    Ninja::~Ninja()
    {
    }

    // functions to implement:
    void Ninja::move(const Character *enemy){}
    void Ninja::slash(Character *enemy) const{}

} // namespace ariel
