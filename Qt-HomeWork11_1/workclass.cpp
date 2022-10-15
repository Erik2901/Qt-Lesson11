#include "workclass.h"
#include <QDebug>

WorkClass::WorkClass(QObject *parent)
    : QObject{parent}
{
    createConnection();
    //createTable();
    QSqlQuery query;
    query.exec("SELECT count (*) FROM exercises");
    while(query.next()){
        count = query.value(0).toInt();
    }
    model = new QSqlQueryModel(this);
    view = new QTableView();
    view->setModel(model);
}

WorkClass::~WorkClass(){
    delete model;
    delete view;
}


bool WorkClass::saveWork()
{
    if(WorkName.size() != 0){
        insertRecord(WorkName, process , QString::number(day) + "." + QString::number(month) + "." + QString::number(year));
        count++;
        return true;
    }
    else{
        return false;
    }

}

void WorkClass::setDay(int newDay)
{
    day = newDay;
}

void WorkClass::setMonth(int newMonth)
{
    month = newMonth;
}

void WorkClass::setYear(int newYear)
{
    year = newYear;
}

void WorkClass::setProcess(int newProcess)
{
    process = newProcess;
}

void WorkClass::setWorkName(const QString &newWorkName)
{
    WorkName = newWorkName;
}

int WorkClass::getCount() const
{
    return count;
}

void WorkClass::openEx()
{
    model->setQuery("SELECT * FROM exercises");
    view->resize(500,300);
    view->show();
}

bool WorkClass::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../Qt-HomeWork11_1/res/exercises.db");
    if(!db.open()){
        qDebug() << "Cant open db";
        return false;
    }
    return true;
}

bool WorkClass::createTable()
{
    QSqlQuery query;
    QString s = "CREATE TABLE exercises ("
                "id INTEGER PRIMARY KEY NOT NULL,"
                "Exercise_Name VARCHAR(15),"
                "Process INTEGER NOT NULL,"
                "End_Date VARCHAR(10));";
    if(!query.exec(s)){
        qDebug() << "Unable to create a table";
        return false;
    }
    return true;
}

bool WorkClass::insertRecord(QString ex_name, int proc, QString d_date)
{
    QSqlQuery query;
    QString s = "INSERT INTO exercises (Exercise_Name, Process, End_Date)"
                "VALUES('%1','%2','%3');";
    QString q = s.arg(ex_name).arg(proc).arg(d_date);
    if(!query.exec(q)){
        qDebug() << "Unable to make insertion";
        return false;
    }
    return true;

}
