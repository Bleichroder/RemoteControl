#include "receive.h"

Receive::Receive(QWidget *parent)
    : QMainWindow(parent)
{
    udpSocket = new QUdpSocket(this);
    port = 23333;
    udpSocket->bind(port, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    QIcon icon(":\\color.png");
    systemTray = new QSystemTrayIcon(this);
    systemTray->setIcon(icon);
    systemTray->setToolTip("Receive");
    quitAct = new QAction("Quit Application", this);
    connect(quitAct, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    pContextMenu = new QMenu(this);
    pContextMenu->addAction(quitAct);
    systemTray->setContextMenu(pContextMenu);
    systemTray->show();
}

Receive::~Receive()
{

}

void Receive::processPendingDatagrams()
{
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int msgType;
        in >> msgType >> x >> y >> width >> height;
        switch(msgType)
        {
            case MouseMove:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_MOVE, x*65535/width, y*65535/height, 0, 0);
            break;
            case MouseLeftClick:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, x*65535/width, y*65535/height,0,0);
                //mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, x*65535/width, y*65535/height,0,0);
            break;
            case MouseRightClick:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, x*65535/width, y*65535/height,0,0);
                //mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, x*65535/width, y*65535/height,0,0);
            break;
            case MouseLeftDblClick:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, x*65535/width, y*65535/height,0,0);
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, x*65535/width, y*65535/height,0,0);
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN, x*65535/width, y*65535/height,0,0);
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, x*65535/width, y*65535/height,0,0);
            break;
            case MouseRightDblClick:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, x*65535/width, y*65535/height,0,0);
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, x*65535/width, y*65535/height,0,0);
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN, x*65535/width, y*65535/height,0,0);
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, x*65535/width, y*65535/height,0,0);
            break;
            case MouseLeftRelease:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP, x*65535/width, y*65535/height,0,0);
            break;
            case MouseRightRelease:
                mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP, x*65535/width, y*65535/height,0,0);
            break;
            case KeyDown:
                keybd_event(x, 0, 0, 0);
            break;
            case KeyUp:
                keybd_event(x, 0, KEYEVENTF_KEYUP, 0);
            break;
            default:
            break;
        }
    }
}
