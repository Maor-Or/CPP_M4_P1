#include "Ninja.hpp"

namespace ariel
{
    class TrainedNinja : Ninja
    {
    private:
        /* data */
    public:
        TrainedNinja(std::string name, Point characterLoction);
        ~TrainedNinja();
    };
    
    TrainedNinja::TrainedNinja(std::string name, Point characterLoction)
    :Ninja(name,characterLoction)
    {
        _hitPoints = 120;
        _speed = 12;
    }
    
    TrainedNinja::~TrainedNinja()
    {
    }
    
} // namespace ariel
