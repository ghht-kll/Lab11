#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractItemModel>
#include "datajson.h"

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex& parent) const override;
    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void copyQVector(QVector<DataJson>* dataJson);
private:
    QVector<DataJson>* dataJson;
};



#endif // MYMODEL_H
