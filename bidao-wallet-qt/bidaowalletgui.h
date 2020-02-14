#ifndef BIDAOWALLETGUI_H
#define BIDAOWALLETGUI_H

#include <QMainWindow>

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <math.h>

#include "seed_generator.h"
#include "currency.h"
#include "coin.h"
#include "wallet.h"


QT_BEGIN_NAMESPACE
namespace Ui { class bidaowalletGUI; }
QT_END_NAMESPACE


class bidaowalletGUI : public QMainWindow
{
    Q_OBJECT

public:
    bidaowalletGUI(QWidget *parent = nullptr);
    ~bidaowalletGUI();


private slots:
    void on_generate_seed_clicked();

    void on_create_new_wallet_clicked();


    void on_b_send_clicked();

private:
    Ui::bidaowalletGUI *ui;

    currency *av_currency;

    seed_generator *gen_s;

    seed_generator seed;

    std::vector<wallet*> wallets;

};

#endif // BIDAOWALLETGUI_H
