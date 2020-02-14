#ifndef CURRENCY_H
#define CURRENCY_H

#include <iostream>
#include <vector>
#include <string>

#include "coin.h"


class currency
{

private:
    std::vector<coin*> available_currency;

public:
    currency();
    std::vector<coin*> get_available_currency();

};

#endif // CURRENCY_H
