#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QUdpSocket>
#include <QKeyEvent>
#include <QApplication>
#include <QLabel>
#include "windows.h"

enum MsgType{MouseMove, MouseLeftClick, MouseRightClick, MouseLeftDblClick, MouseRightDblClick, MouseLeftRelease, MouseRightRelease, KeyDown, KeyUp};

class RemoteControl : public QMainWindow
{
    Q_OBJECT

public:
    RemoteControl(QWidget *parent = 0);
    ~RemoteControl();
private:
    //QHBoxLayout *mainLayout;
    //QLabel *labelMousePos;
    QUdpSocket *udpSocket;
    qint16 port;
    int drag;
    int width, height;
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    //void keyPressEvent(QKeyEvent *);
    //void keyReleaseEvent(QKeyEvent *);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    //bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);
};

#endif // REMOTECONTROL_H
