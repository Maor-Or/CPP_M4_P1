#include "Cowboy.hpp"

namespace ariel
{
    // constructors:
    Cowboy::Cowboy(std::string name, Point characterLoction)
        : Character(name, characterLoction), _bulletAmount(BULLETAMOUNT)
    {
        _hitPoints = COWBOY_HP;
    }

    Cowboy::~Cowboy()
    {
    }

    // functions to implement:
    void Cowboy::shoot(Character *enemy) const {}
    bool Cowboy::hasboolets() const {return _bulletAmount > 0;}
    void Cowboy::reload() {}

} // namespace ariel
