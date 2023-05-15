#include "Ninja.hpp"

namespace ariel
{
    class YoungNinja : Ninja
    {
    private:
        /* data */
    public:
        YoungNinja(std::string name, Point characterLoction);
        ~YoungNinja();
    };
    
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
