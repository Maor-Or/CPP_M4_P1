#pragma once

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
  
    
} // namespace ariel
