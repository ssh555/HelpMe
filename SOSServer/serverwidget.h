#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <qtcpserver.h> //监听套接字
#include <qtcpsocket.h> //通信套接字

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWidget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private slots:

private:
    Ui::ServerWidget *ui;

    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通信套接字

    //获取接收的信息的标题
    QString GetSocketDataTitle(QString );
    //获取接收的信息的内容
    QString GetSocketDatas(QString );
    //与数据库中数据比较用户名与密码是否匹配
    bool CompareUerPass(QString datas);
};
#endif // SERVERWIDGET_H
