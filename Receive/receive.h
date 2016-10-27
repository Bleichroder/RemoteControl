#ifndef RECEIVE_H
#define RECEIVE_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QUdpSocket>
#include <QAction>
#include <QMenu>
#include <QApplication>
#include "windows.h"

enum MsgType{MouseMove, MouseLeftClick, MouseRightClick, MouseLeftDblClick, MouseRightDblClick, MouseLeftRelease, MouseRightRelease, KeyDown, KeyUp};

class Receive : public QMainWindow
{
    Q_OBJECT

public:
    Receive(QWidget *parent = 0);
    ~Receive();
private:
    QSystemTrayIcon *systemTray;
    QAction *quitAct;
    QMenu *pContextMenu;
    QUdpSocket *udpSocket;
    qint16 port;
    int x, y, width, height;
private slots:
    void processPendingDatagrams();
};

#endif // RECEIVE_H
