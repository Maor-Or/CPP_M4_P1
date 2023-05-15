#pragma once

#include "Ninja.hpp"

namespace ariel
{
    class TrainedNinja : public Ninja
    {
    private:
        /* data */
    public:
        TrainedNinja(std::string name, Point characterLoction);
        ~TrainedNinja();
    };
   
    
} // namespace ariel
