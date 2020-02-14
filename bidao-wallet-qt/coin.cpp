#include "coin.h"

coin::coin()
{
    this->name = "";
    this->ticker = "";
}

coin::coin(std::string n, std::string t)
{
    this->name = n;
    this->ticker = t;
}

void coin::set_name(std::string n)
{
    this->name = n;
}

void coin::set_ticker(std::string t)
{
    this->ticker = t;
}
