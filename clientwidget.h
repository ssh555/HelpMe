#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket> //通信套接字

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
private:
    Ui::ClientWidget *ui;

    QTcpSocket *tcpSocket;

    //获取接收的信息的标题
    QString GetSocketDataTitle(QString );
    //获取接收的信息的内容
    QString GetSocketDatas(QString );
};

#endif // CLIENTWIDGET_H
