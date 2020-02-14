#ifndef COIN_H
#define COIN_H


#include <iostream>
#include <vector>
#include <string>

class coin
{
private:
    std::string name;
    std::string ticker;

public:
    coin();
    coin(std::string n, std::string t);

    std::string get_name();
    std::string get_ticker();

    void set_name(std::string n);
    void set_ticker(std::string t);
};

#endif // COIN_H
