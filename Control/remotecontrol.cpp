#include "remotecontrol.h"

RemoteControl::RemoteControl(QWidget *parent)
    : QMainWindow(parent)
{
    udpSocket = new QUdpSocket(this);
    port = 23333;
    udpSocket->bind(port, QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    setCursor(Qt::CrossCursor); //设置鼠标为十字星
    //labelMousePos = new QLabel(this);
    //labelMousePos->setText(tr(""));
    //labelMousePos->setFixedWidth (100);
    //mainLayout = new QHBoxLayout(this);
    //mainLayout->addWidget(labelMousePos);
    this->setMouseTracking (true);//自动跟踪鼠标（默认情况下，mouseMoveEvent响应你按下鼠标的某个键的鼠标移动。）
    showFullScreen();
    width = geometry().width();
    height = geometry().height();
}

RemoteControl::~RemoteControl()
{

}

void RemoteControl::mouseMoveEvent(QMouseEvent *e)
{
    //1.获取局部鼠标位置
    //labelMousePos ->setText("("+QString::number(e->x())+","+QString::number(e->y())+")");
    //2.获取全局鼠标位置
    drag = 0;
    if(e->buttons() & Qt::LeftButton)
    {
           drag = 1;
    }
    if(e->buttons() & Qt::RightButton)
    {
           drag = 2;
    }
    QPoint coursePoint;
    coursePoint = QCursor::pos();//获取当前光标的位置
    //labelMousePos ->setText("("+QString::number(coursePoint.x())+","+QString::number(coursePoint.y())+")");
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << MouseMove << coursePoint.x() << coursePoint.y() << width << height;
    udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}

void RemoteControl::mousePressEvent (QMouseEvent * e )//鼠标单击事件响应
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    if(e->button()==Qt::LeftButton){
        drag = 1;
        out << MouseLeftClick << e->x() << e->y() << width << height;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
    }
    else if(e->button()==Qt::RightButton){
        drag = 2;
        out << MouseRightClick << e->x() << e->y() << width << height;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
    }
}

void RemoteControl::mouseDoubleClickEvent( QMouseEvent * e )//鼠标双击事件响应
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    if(e->button()==Qt::LeftButton){
        out << MouseLeftDblClick << e->x() << e->y() << width << height;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
    }
    else if(e->button()==Qt::RightButton){
        out << MouseRightDblClick << e->x() << e->y() << width << height;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
    }
}

void RemoteControl::mouseReleaseEvent ( QMouseEvent * e )//鼠标松开事件响应
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    if(drag == 1)
    {
        out << MouseLeftRelease << e->x() << e->y() << width << height;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
    }
    if(drag == 2)
    {
        out << MouseRightRelease << e->x() << e->y() << width << height;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
    }
}

bool RemoteControl::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = static_cast<MSG*>(message);
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    switch(msg->message)
    {
    case WM_SYSKEYDOWN:
        out << KeyDown << msg->wParam << 0 << 0 << 0;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
        return false;
    break;
    case WM_SYSKEYUP:
        out << KeyUp << msg->wParam << 0 << 0 << 0;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
        return false;
    break;
    case WM_KEYDOWN:
        if(msg->wParam == VK_LWIN || msg->wParam == VK_RWIN)
        {
            out << KeyDown << msg->wParam << 0 << 0 << 0;
            udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
            return false;
        }
        if(msg->wParam == VK_ESCAPE)
        {
            qApp->quit();
        }
        out << KeyDown << msg->wParam << 0 << 0 << 0;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
        return false;
    break;
    case WM_KEYUP:
        out << KeyUp << msg->wParam << 0 << 0 << 0;
        udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
        return false;
    break;
    }
}

/*void RemoteControl::keyPressEvent(QKeyEvent *k)
{
    if(k->key() == Qt::Key_Escape)
    {
        qApp->quit();
    }
    if(k->modifiers() != Qt::ControlModifier)
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << KeyDown << k->key();
    udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}

void RemoteControl::keyReleaseEvent(QKeyEvent *k)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << KeyUp << k->key() << 0 << 0 << 0;
    udpSocket->writeDatagram(data, data.length(), QHostAddress::Broadcast, port);
}*/
