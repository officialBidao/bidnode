#include "seed_generator.h"

seed_generator::seed_generator()
{
    if(this->load() != true){
        exit(0);
    }
}

std::string seed_generator::generate_seed()
{
    return "";
}

bool seed_generator::load(){

    return true;
}
