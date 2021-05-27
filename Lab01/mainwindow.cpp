#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymodel.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // MyModel* model = new MyModel(this);
   // model->add("grefv",23,"grfs");
   // model->add("grefv",33,"grthgefs");
//    ui->tableView_2->setModel(model);
    this->model = new MyModel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(this->isEmptyPath())
    {
        this->ReadingDataFromAFile();
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(this->isEmptyPath() && this->isEmptyVector())
    {
        this->DataDisplay();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(this->dataJson.count() >= this->ui->spinBoxChange->text().toInt() && this->isEmptyPath() && this->isEmptyVector())
    {
        this->dataJson[this->ui->spinBoxChange->text().toInt()].SetName(this->ui->lineEditSetName->text());
        this->dataJson[this->ui->spinBoxChange->text().toInt()].SetAge(this->ui->lineEditSetAge->text().toInt());
        this->dataJson[this->ui->spinBoxChange->text().toInt()].SetPhoneNumber(this->ui->lineEditSetTel->text());
        this->WritingDataToAFile();
        this->ReadingDataFromAFile();
        this->DataDisplay();
    }
}

void MainWindow::DataDisplay()
{
    if(this->dataJson.count() != 0)
    {
       /* // QAbstractTableModel
        this->qStandardItemModel = new QStandardItemModel();
        qStandardItemModel->setHorizontalHeaderLabels(QStringList()<<"Name"<<"Age"<<"Tel");

        for(QVector<DataJson>::Iterator i = this->dataJson.begin(); i != this->dataJson.end(); i++)
        {
            QStandardItem* itemCol1(new QStandardItem(i->GetName()));
            QStandardItem* itemCol2(new QStandardItem(QString::number(i->GetAge())));
            QStandardItem* itemCol3(new QStandardItem(i->GetPhoneNumber()));
            qStandardItemModel->appendRow(QList<QStandardItem*>()<<itemCol1<<itemCol2<<itemCol3);
        }
        ui->tableView->setModel(qStandardItemModel);
*/

        this->model = new MyModel(this);
        this->model->copyQVector(&this->dataJson);
        this->ui->tableView->setModel(model);
    }
    else
    {
        QMessageBox::information(nullptr,"Ошибка","Данные не записаны в QVector");
    }
}

void MainWindow::ReadingDataFromAFile() // чтение данных (метод)
{
    this->dataJson.clear(); //
    if(this->file.open(QIODevice::ReadOnly | QFile::Text))
    {
    this->qJsonDocument = QJsonDocument::fromJson(QByteArray(this->file.readAll()));
    this->file.close();
    this->qJsonArray = QJsonArray(this->qJsonDocument.object().value("workers").toArray());
        for(int i = 0; i < this->qJsonArray.count(); i++)
        {
            std::shared_ptr<DataJson> data(new DataJson());
            data->SetName(this->qJsonArray.at(i).toObject().value("name").toString());
            data->SetAge(this->qJsonArray.at(i).toObject().value("age").toInt());
            data->SetPhoneNumber((this->qJsonArray.at(i).toObject().value("tel").toString()));
            this->dataJson.push_back(*data);
        }
        QMessageBox::information(nullptr,"Готово","Данные записаны");
     }
     else
     {
        QMessageBox::information(nullptr,"Ошибка","Файл не открылся");
     }
}

void MainWindow::AddNewEntry()
{
    if(this->file.open(QIODevice::WriteOnly))
    {
        QVariantMap variantMap;
        variantMap.insert("name",ui->lineEditSetName->text());
        variantMap.insert("age",ui->lineEditSetAge->text().toInt());
        variantMap.insert("tel",ui->lineEditSetTel->text());
        QJsonObject json = QJsonObject::fromVariantMap(variantMap);
        QJsonArray docToWrite = this->qJsonDocument.object().value("workers").toArray();
        docToWrite.append(json);
        this->qJsonDocument.setArray(docToWrite);
        this->file.write("{\"workers\":" + this->qJsonDocument.toJson() + "}");
        this->file.close();
    }
}

void MainWindow::WritingDataToAFile()
{
    QJsonObject recordObject;
    this->qJsonDocument = QJsonDocument();
    this->qJsonArray = QJsonArray();
    for(QVector<DataJson>::Iterator i = this->dataJson.begin(); i != this->dataJson.end(); i++)
    {
        recordObject.insert("name",QJsonValue::fromVariant(i->GetName()));
        recordObject.insert("age",QJsonValue::fromVariant((i->GetAge())));
        recordObject.insert("tel",QJsonValue::fromVariant(i->GetPhoneNumber()));
        this->qJsonArray.push_back(recordObject);
    }
    QJsonDocument doc(this->qJsonArray);
    file.setFileName(this->path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write("{\"workers\":" + doc.toJson() + "}");
    file.close();
}

void MainWindow::on_pushButton_5_clicked()
{
    if(this->isEmptyPath() && this->isEmptyVector() && this->isEmptyLineEdit())
    {
        this->AddNewEntry();
        this->ReadingDataFromAFile();
        this->DataDisplay();
    }
}

void MainWindow::on_pushButton_DeleteRow_clicked()
{
    if(this->dataJson.count() >= this->ui->spinBoxDel->text().toInt() && this->isEmptyPath() && this->isEmptyVector())
    {
        this->dataJson.remove(this->ui->spinBoxDel->text().toInt());
        this->WritingDataToAFile();
        this->DataDisplay();
    }
}

bool MainWindow::isEmptyPath()
{
    if(this->path == nullptr)
    {
        QMessageBox::information(nullptr,"Ошибка","Путь к файлу не выбран");
        return false;
    }
    else return true;
}

bool MainWindow::isEmptyVector()
{
    if(this->dataJson.length() == 0)
    {
        QMessageBox::information(nullptr,"Ошибка","Qvector пуст");
        return false;
    }
    else return true;
}

bool MainWindow::isEmptyLineEdit()
{
    if(this->ui->lineEditSetName->text() == nullptr ||this->ui->lineEditSetAge->text() == nullptr|| this->ui->lineEditSetTel->text() == nullptr)
    {
        QMessageBox::information(nullptr,"Ошибка","Данные введены некорректно");
        return false;
    }
    else return true;
}

void MainWindow::on_action_triggered()
{
    this->path = QFileDialog::getOpenFileName(nullptr,"","","*.json");
    this->file.setFileName(this->path);
}
