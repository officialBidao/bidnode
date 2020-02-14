#include "bidaowalletgui.h"
#include "ui_bidaowalletgui.h"


//init
bidaowalletGUI::bidaowalletGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::bidaowalletGUI)
{
    ui->setupUi(this);

    this->av_currency = new currency();
}


//destructor
bidaowalletGUI::~bidaowalletGUI()
{
    delete ui;
}


//generating new seed
void bidaowalletGUI::on_generate_seed_clicked()
{
    //get a new seed
    std::string new_seed = gen_s->generate_seed();

    //show seed in ui
    ui->f_seed->setText(new_seed.c_str());
}


//generate the wallet
void bidaowalletGUI::on_create_new_wallet_clicked()
{
    //create new wallet
    wallet *w = new wallet();

    //get seed
    std::string s = ui->f_seed->toPlainText().toStdString();
    w->create_wallet(s);
}


//send transaction
void bidaowalletGUI::on_b_send_clicked()
{

}
