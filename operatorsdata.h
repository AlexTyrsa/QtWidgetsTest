#pragma once

#include <QAbstractItemModel>

class DBDriver;

class OperatorsData : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit OperatorsData(const QString &pathToDB, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    DBDriver* m_db_driver;

};
