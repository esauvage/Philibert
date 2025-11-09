#include "philmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhilMainWindow w;
    w.show();
    return a.exec();
}
