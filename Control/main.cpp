#include "remotecontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RemoteControl w;
    w.show();

    return a.exec();
}
