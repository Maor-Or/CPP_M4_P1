#pragma once

#include "Team.hpp"

namespace ariel
{
    class SmartTeam : public Team 
    {
    private:
        /* data */
    public:
        SmartTeam(Character *leader);
        ~SmartTeam();
    };
    
} // namespace ariel
