#ifndef SEED_GENERATOR_H
#define SEED_GENERATOR_H

#include<string>


class seed_generator
{
private:
    bool load();
public:
    seed_generator();
    std::string generate_seed();
};


#endif // SEED_GENERATOR_H
