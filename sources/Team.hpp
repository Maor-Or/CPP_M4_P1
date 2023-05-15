#pragma once

#include "Point.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"

namespace ariel
{
    class Team
    {
    private:
        Character *_leader;

    public:
        // constructors:
        Team(Character *leader);
        ~Team();

        // functions to implement:
        void add(Character *newTeamMember);
        void attack(Team * enemyTeam);
        int stillAlive(); 
        void print();
    };

};