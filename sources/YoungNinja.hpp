#pragma once

#include "Ninja.hpp"
#include <string>

namespace ariel
{
    class YoungNinja : public Ninja
    {
    private:
        /* data */
    public:
        YoungNinja(std::string name, Point characterLoction);
        ~YoungNinja();
    };
    
   
    
} // namespace ariel
