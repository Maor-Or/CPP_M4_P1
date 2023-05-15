#include "Ninja.hpp"

namespace ariel
{
    class OldNinja : public Ninja
    {
    private:
        /* data */
    public:
        OldNinja(std::string name, Point characterLoction);
        ~OldNinja();
    };
    
    OldNinja::OldNinja(std::string name, Point characterLoction)
    :Ninja(name,characterLoction)
    {
        _hitPoints = 150;
        _speed = 8;
    }
    
    OldNinja::~OldNinja()
    {
    }
    
} // namespace ariel
