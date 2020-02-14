#include "currency.h"

currency::currency()
{
    coin *c1 = new coin();
    c1->set_name("Bidao");
    c1->set_name("BID");

    coin *c2 = new coin();
    c2->set_name("Bidao Stable");
    c2->set_name("BDS");

    this->available_currency.push_back(c1);
    this->available_currency.push_back(c2);
}


std::vector<coin*> currency::get_available_currency(){
    return this->available_currency;
}
