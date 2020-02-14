#include "bidaowalletgui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bidaowalletGUI w;
    w.show();
    return a.exec();
}
