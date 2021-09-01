#include "sqldoctorsmgr.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>

#include <QSqlTableModel>
#include <QSqlRecord>

#include <QVariant>
#include <QByteArray>
#include <QBuffer>

#include <QDebug>


//private
SqlDoctorsMgr::SqlDoctorsMgr(QObject *parent) : QObject(parent)
{
    ConnectSqlDoctors("127.0.0.1",3306);
}

void SqlDoctorsMgr::ConnectSqlDoctors(QString ip,qint16 port){
    //添加MySQL数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //连接数据库
    db.setHostName(ip); //数据库服务器IP
    db.setPort(port);//设置端口
    db.setUserName("projectHelpMe"); //数据库用户名
    db.setPassword("123456"); //密码
    db.setDatabaseName("helpme_patientsdata"); // 使用哪个数据库

    //打开数据库
    if(!db.open()){//数据库打开失败
        QMessageBox::warning(NULL,"数据库连接失败",db.lastError().text());
        return;
    }
    query = new QSqlQuery;
    qDebug() << "已连接至数据库";
}
//根据某一个数据及其在数据库中的名字查询相关数据
QList<DoctorData>* SqlDoctorsMgr::SelectDoctor(QString dataType,QString data){
    QList<DoctorData> *list = new QList<DoctorData>;
    query->exec(QString("SELECT * FROM `helpme_patientsdata`.`doctors` WHERE `%1` = '%2';").arg(dataType).arg(data));
    while(query->next()){ //一行一行遍历
        //取出当前行的内容
        DoctorData temp;
        temp.id = query->value("id").toInt();
        temp.name = query->value("name").toString();
        temp.IDCardNum = query->value("IDCardNum").toString();
        temp.username = query->value("username").toString();
        temp.password = query->value("password").toString();
        temp.patientsID = query->value("patientsID").toString();
        list->append(temp);
    }
    return list;
}

//public
DoctorData SqlDoctorsMgr::SelectDoctor(QString username){
    QList<DoctorData> *list = SelectDoctor("username",username);
    if(list->size() <= 0){
        DoctorData d;
        return d;
    }

    return SelectDoctor("username",username)->at(0);
}


SqlDoctorsMgr* SqlDoctorsMgr::m_instance = NULL;

