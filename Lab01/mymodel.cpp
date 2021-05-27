#include "mymodel.h"

MyModel::MyModel(QObject *parent) : QAbstractTableModel(parent){    }

int MyModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    return this->dataJson->size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch (index.column())
        {
            case 0:
                return this->dataJson->at(index.row()).GetName();
                break;
            case 1:
                return this->dataJson->at(index.row()).GetAge();
                break;
            case 2:
                return this->dataJson->at(index.row()).GetPhoneNumber();
                break;
        }
    }
    return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch (section)
            {
                case 0:
                    return "Name";
                case 1:
                    return "Age";
                case 2:
                    return "phoneNumber";
            }
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

void MyModel::copyQVector(QVector<DataJson> *dataJson)
{
    this->dataJson = dataJson;
}



