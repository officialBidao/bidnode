#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <vector>
#include <string>


class wallet
{
private:
    std::string address;

public:
    wallet();

    void create_wallet(std::string seed);

    bool create_transaction(double amount, std::string currency);
};

#endif // WALLET_H
