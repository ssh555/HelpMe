#include "serverwidget.h"
#include "ui_serverwidget.h"

#include <qdebug.h>

#include <sqldoctorsmgr.h>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    setWindowTitle("服务器:8888");

    tcpServer = NULL;
    tcpSocket = NULL;

    //监听套接字，指定父对象，让其自动回收空间
    tcpServer = new QTcpServer(this);
    //监听端口
    tcpServer->listen(QHostAddress::Any,8888);
    //接收客户端的连接
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //获取对方的IP和端口
//        QString ip = tcpSocket->peerAddress().toString();
//        qint16 port = tcpSocket->peerPort();
        //接收客户端发送的数据
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //获取对方发送的内容
            QByteArray array = tcpSocket->readAll();
            QString str = QString(array);
            QString title = GetSocketDataTitle(str);
            QString datas = GetSocketDatas(str);
            //获取的内容为登录内容
            if(title.compare("login") == 0){
                //成功登录
                if(CompareUerPass(datas)){
                    tcpSocket->write(QString("login###true").toUtf8().data());
                }
                //用户名或密码错误
                else{
                    tcpSocket->write(QString("login###false").toUtf8().data());
                }
            }
        });
    });


}

ServerWidget::~ServerWidget()
{
    delete ui;
}

//获取信息的标题
QString ServerWidget::GetSocketDataTitle(QString str){
    return str.mid(0,str.indexOf("###"));
}
//获取信息的内容
QString ServerWidget::GetSocketDatas(QString str){
    return str.mid(3+str.indexOf("###"));
}
//与数据库中数据比较用户名与密码是否匹配
bool ServerWidget::CompareUerPass(QString datas){
    QString userName = datas.mid(datas.indexOf(":")+1,datas.indexOf("$")-2);
    QString passWord = datas.mid(datas.lastIndexOf(":")+1);
    //获取数据库中的唯一的用户名及其密码
    DoctorData doctor = SqlDoctorsMgr::Instance()->SelectDoctor(userName);
    if(doctor.username == NULL)
        return false;
    QString SQLUserName = doctor.username;
    QString SQLPassWord = doctor.password;
    if(userName.compare(SQLUserName) == 0 && passWord.compare(SQLPassWord) == 0)
        return true;
    else
        return false;
}


