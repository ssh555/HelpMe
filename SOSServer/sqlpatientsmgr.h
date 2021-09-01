#ifndef SQLPATIENTSMGR_H
#define SQLPATIENTSMGR_H

#include <QObject>

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDate>
#include <QPixmap>

#include <QSqlTableModel>
#include <QSqlRecord>


struct PatientData{
    int id;//病人编号
    QString name;//病人姓名
    QDate HPTDate;//病人入院时间
    QPixmap photo;//病人照片
    QString photoType;//照片的格式 "jpg" "png" 等
    int age;//病人年龄
    QString IDCardNum;//身份证号
    int* ECGArray;//心率
    int* spO2Array;//血氧饱和度
    int* RESPArray;//呼吸率

};//存放数据库中获得的一行数据

class SqlPatientsMgr : public QObject
{
    Q_OBJECT
public:


    static SqlPatientsMgr* Instance(){
        if(m_instance == NULL)
            m_instance = new SqlPatientsMgr();
        return  m_instance;
    }

    //查询病人信息，返回病人的所有数据库信息::类型为结构体PatientData*
    PatientData SelectPatient(int id);//根据id查询
    QList<PatientData>* SelectPatient(QString name);//根据姓名查询，返回所有同名的病人信息
    QList<PatientData>* SelectPatient(QDate HPTDate);//根据入院时间查询
    PatientData SelectPatient(QString IDCardNum,int i);//根据身份证号查询
    //查询所有的病人信息，返回所有病人的信息::QList<PatientData>*
    QList<PatientData>* SelectPatientAll();

    //增加数据,返回TRUE表示添加成功，反之失败
    bool AddPatientRecord(PatientData data,bool isAddId);//isAddId为TRUE表示id自增，为false表示使用data里面的id

    //改变指定行的数据,只会更新心率，血氧饱和度，呼吸率,不能更改病人个人基本信息,返回TRUE表示添加成功，反之失败
    bool UpdatePatientData(PatientData data);

    //删除指定的数据行
    bool DeletePatientData(int id);//根据id删除
    bool DeletePatientData(QString IDCardNum);//根据身份证号删除


private:
    explicit SqlPatientsMgr(QObject *parent = nullptr);
    static SqlPatientsMgr* m_instance;
    bool isConnectSql = false;//true表示已连接至数据库   false表示未连接至数据库
    QSqlQuery *query; //用于执行MySQL语句


    //连接数据库
    void ConnectSqlPatients(QString ip,qint16 port);//返回TRUE表示成功连接  FALSE表示连接失败
    //根据某一个数据及其在数据库中的名字查询相关数据，返回QList<PatientData>*
    QList<PatientData>* SelectPatient(QString dataType,QString data);
    //删除某行的所有数据
    bool DeletePatientData(QString name,QString data);

    //QStringList转int*
    int* StrListToIntArr(QStringList list);
    //int*转QString
    QString IntArrToStr(int* nums);


signals:

};

#endif // SQLPATIENTSMGR_H


