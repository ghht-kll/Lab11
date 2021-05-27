#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVector>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QStandardItemModel>
#include <QMessageBox>
#include <memory>
#include <QDebug>
#include <QList>
#include <QVariantMap>
#include "datajson.h"
#include "mymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_DeleteRow_clicked();

    void on_action_triggered();

private:
    bool isEmptyPath();
    bool isEmptyVector();
    bool isEmptyLineEdit();
    void ReadingDataFromAFile();
    void WritingDataToAFile();
    void AddNewEntry();
    void DataDisplay();

private:
    Ui::MainWindow *ui;
    QJsonDocument qJsonDocument;
    QJsonArray qJsonArray;
    QString path = nullptr;
    QVector<QString> data;
    QFile file;
    QVector<DataJson> dataJson; // структура данных вектор
    //QStandardItemModel* qStandardItemModel;
    MyModel* model;
};
#endif // MAINWINDOW_H
