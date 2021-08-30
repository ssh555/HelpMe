#include "sqlpatientsmgr.h"

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
SqlPatientsMgr::SqlPatientsMgr(QObject *parent) : QObject(parent)
{
    ConnectSqlPatients("10.195.76.197",3306);
}

void SqlPatientsMgr::ConnectSqlPatients(QString ip,qint16 port){
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
        isConnectSql = false;
    }
    isConnectSql = true;
    query = new QSqlQuery;
    qDebug() << "已连接至数据库";
}

int* SqlPatientsMgr::StrListToIntArr(QStringList list){
    int len = list.size();
    int *nums = new int[len+1];
    nums[0] = len;
    for(int i = 1;i <= len; ++i){
        nums[i] = list.at(i-1).toInt();
    }
    return nums;
}
QString SqlPatientsMgr::IntArrToStr(int *nums){
    int len = nums[0];
    QString str = "";
    for(int i = 1;i < len; ++i){
        str += QString("%1,").arg(nums[i]);
    }
    str += QString("%1").arg(nums[len]);
    return str;
}

//public

//根据某一个数据及其在数据库中的名字查询相关数据
QList<PatientData>* SqlPatientsMgr::SelectPatient(QString dataType,QString data){
    //如果没有连接数据库，则连接数据库
    if(!isConnectSql){
        ConnectSqlPatients();
    }
    QList<PatientData> *list = new QList<PatientData>;
    query->exec(QString("SELECT * FROM `helpme_patientsdata`.`patients` WHERE %1 = '%2';").arg(dataType).arg(data));
    while(query->next()){ //一行一行遍历
        //qDebug() << query->value("name");
        //取出当前行的内容
        PatientData temp;
        temp.id = query->value("id").toInt();
        temp.age = query->value("age").toInt();
        temp.name = query->value("name").toString();
        temp.photo.loadFromData( query->value("photo").toByteArray() );
        temp.photoType = query->value("photoType").toString();
        QString str = query->value("HPTDate").toString();
        QStringList strl = query->value("HPTDate").toString().split("-");
        temp.HPTDate.setDate(strl.at(0).toInt(),strl.at(1).toInt(),strl.at(2).toInt());
        temp.IDCardNum = query->value("IDCardNum").toString();

        temp.ECGArray = StrListToIntArr(query->value("ECG").toString().split(","));
        temp.spO2Array = StrListToIntArr(query->value("spO2").toString().split(","));
        temp.RESPArray = StrListToIntArr(query->value("RESP").toString().split(","));
        list->append(temp);
    }
    return list;
}
//根据id查询
PatientData SqlPatientsMgr::SelectPatient(int id){
    return  SelectPatient("id",QString::number(id))->at(0);
}
//根据姓名查询，返回所有同名的病人信息
QList<PatientData>* SqlPatientsMgr::SelectPatient(QString name){
    return  SelectPatient("name",name);
}
//根据入院时间查询
QList<PatientData>* SqlPatientsMgr::SelectPatient(QDate HPTDate){
    return  SelectPatient("HPTDate",HPTDate.toString("yyyy-MM-dd"));
}
//根据身份证号查询
PatientData SqlPatientsMgr::SelectPatient(QString IDCardNum,int i){
    return  SelectPatient("IDCardNum",IDCardNum)->at(0);
}
//查询所有的病人信息，返回所有病人的信息::QList<PatientData>*
QList<PatientData>* SqlPatientsMgr::SelectPatientAll(){
    //如果没有连接数据库，则连接数据库
    if(!isConnectSql){
        ConnectSqlPatients();
    }
    QList<PatientData> *list = new QList<PatientData>;
    query->exec(QString("SELECT * FROM `helpme_patientsdata`.`patients`;"));
    while(query->next()){ //一行一行遍历
        //取出当前行的内容
        PatientData temp;
        temp.id = query->value("id").toInt();
        temp.age = query->value("age").toInt();
        temp.name = query->value("name").toString();
        temp.photo.loadFromData( query->value("photo").toByteArray() );
        temp.photoType = query->value("photoType").toString();
        QStringList strl = query->value("HPTDate").toString().split("-");
        temp.HPTDate.setDate(strl.at(0).toInt(),strl.at(1).toInt(),strl.at(2).toInt());
        temp.IDCardNum = query->value("IDCardNum").toString();

        temp.ECGArray = StrListToIntArr(query->value("ECG").toString().split(","));
        temp.spO2Array = StrListToIntArr(query->value("spO2").toString().split(","));
        temp.RESPArray = StrListToIntArr(query->value("RESP").toString().split(","));
        list->append(temp);
    }
    return list;
}

//增加数据
bool SqlPatientsMgr::AddPatientRecord(PatientData data, bool isAddId){
    QByteArray ba;
    QBuffer imgbuffer(&ba);
    imgbuffer.open(QIODevice::WriteOnly);
    data.photo.save(&imgbuffer,data.photoType.toUtf8(),100);

    QString ECGStr = IntArrToStr(data.ECGArray);
    QString spO2Str = IntArrToStr(data.spO2Array);
    QString RESPStr = IntArrToStr(data.RESPArray);

    QVariant photo(ba);
    if(isAddId){
        query->prepare(QString("INSERT INTO `helpme_patientsdata`.`patients`"
                               "(`id`,`name`,`HPTDate`,`photo`,`photoType`,`age`,`IDCardNum`,`ECG`,`spO2`,`RESP`) "
                               "VALUES('%1','%2','%3','?','%4','%5','%6','%7','%8','%9')"
                               ";").arg(data.id).arg(data.name).arg(data.HPTDate.toString("yyyy-MM-dd")).arg(data.photoType).arg(data.age).arg(data.IDCardNum).arg(ECGStr).arg(spO2Str).arg(RESPStr));
    }
    else{
        query->prepare(QString("INSERT INTO `helpme_patientsdata`.`patients`"
                               "(`name`,`HPTDate`,`photo`,`photoType`,`age`,`IDCardNum`,`ECG`,`spO2`,`RESP`) "
                               "VALUES('%1','%2',?,'%3','%4','%5','%6','%7','%8')"
                               ";").arg(data.name).arg(data.HPTDate.toString("yyyy-MM-dd")).arg(data.photoType).arg(data.age).arg(data.IDCardNum).arg(ECGStr).arg(spO2Str).arg(RESPStr));
    }
    query->addBindValue(photo);
    if(!query->exec())
    {
        qDebug()<<query->lastError().text().toLocal8Bit().data();
        return false;
    }
    return true;
}


//更新数据
bool SqlPatientsMgr::UpdatePatientData(PatientData data){
    QString ECGStr = IntArrToStr(data.ECGArray);
    QString spO2Str = IntArrToStr(data.spO2Array);
    QString RESPStr = IntArrToStr(data.RESPArray);
    query->prepare(QString("UPDATE `helpme_patientsdata`.`patients`"
                           " SET ,`ECG` = '?',`spO2` = '?',`RESP` = '?' "
                           "WHERE `id` = '%1' AND `name` = '%2' AND `IDCardNum` = '%3'"
                           ";").arg(data.id).arg(data.name).arg(data.IDCardNum));
    QVariant ECG(ECGStr);
    QVariant spO2(spO2Str);
    QVariant RESP(RESPStr);
    query->addBindValue(ECG);
    query->addBindValue(spO2);
    query->addBindValue(RESP);
    if(!query->exec())
    {
        qDebug()<<query->lastError().text().toLocal8Bit().data();
        return false;
    }
    return true;
}


//删除某行所有数据
bool SqlPatientsMgr::DeletePatientData(QString name, QString data){
    query->prepare(QString("DELETE FROM `helpme_patientsdata`.`patients`"
                           " WHERE %1 = '%2'"
                           ";").arg(name).arg(data));
    if(!query->exec())
    {
        qDebug()<<query->lastError().text().toLocal8Bit().data();
        return false;
    }
    return true;
}
bool SqlPatientsMgr::DeletePatientData(int id){
    return DeletePatientData("id",QString::number(id));
}
bool SqlPatientsMgr::DeletePatientData(QString IDCardNum){
    return DeletePatientData("IDCardNum",IDCardNum);
}

SqlPatientsMgr* SqlPatientsMgr::m_instance = NULL;
