#include "Team.hpp"

namespace ariel
{
    // Ctors&Dtors:
    Team::Team(Character *leader) : _leader(leader)
    {
    }

    Team::~Team()
    {
    }

    // functions to implement:
    void Team::add(Character *newTeamMember){}
    void Team::attack(Team *enemyTeam){}
    int Team::stillAlive(){return 0;}
    void Team::print(){}
};