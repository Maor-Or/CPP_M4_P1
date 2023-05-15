#include "YoungNinja.hpp"

namespace ariel
{

 YoungNinja::YoungNinja(std::string name, Point characterLoction)
    :Ninja(name,characterLoction)
    {
        _hitPoints = 100;
        _speed = 14;
    }
    
    YoungNinja::~YoungNinja()
    {
    }
    
} // namespace ariel