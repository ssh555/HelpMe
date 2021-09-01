#ifndef SQLDOCTORSMGR_H
#define SQLDOCTORSMGR_H

#include <QObject>

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include <QPixmap>

#include <QSqlTableModel>
#include <QSqlRecord>


struct DoctorData{
    int id;//医生编号
    QString name;//医生姓名
    QString IDCardNum;//身份证号
    QString username;//用户名
    QString password;//密码
    QString patientsID;//管理的病人的ID

};//存放数据库中获得的一行数据

class SqlDoctorsMgr : public QObject
{
    Q_OBJECT
public:


    static SqlDoctorsMgr* Instance(){
        if(m_instance == NULL)
            m_instance = new SqlDoctorsMgr();
        return  m_instance;
    }

    //查询医生信息，返回医生的所有数据库信息::类型为结构体DoctorData*
    DoctorData SelectDoctor(QString username);//根据用户名查询


private:
    explicit SqlDoctorsMgr(QObject *parent = nullptr);
    static SqlDoctorsMgr* m_instance;
    QSqlQuery *query; //用于执行MySQL语句


    //连接数据库
    void ConnectSqlDoctors(QString ip,qint16 port);//返回TRUE表示成功连接  FALSE表示连接失败
    //根据某一个数据及其在数据库中的名字查询相关数据，返回QList<DoctorData>*
    QList<DoctorData>* SelectDoctor(QString dataType,QString data);

signals:

};

#endif // SQLDoctorsSMGR_H



