#pragma once

#include <QAbstractItemModel>

class DBDriver;
class country_t;

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

    QSharedPointer<country_t> get_country_by_id(int id) const;

    void changeOperatorName(int mcc, int mnc, const QString& name);
    void createNewOperator(int mcc, int mnc, const QString& name);

signals:
    void requestRefresh();
    void requestRebuild();

private:
    DBDriver* m_db_driver;

};
