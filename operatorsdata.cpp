#include "operatorsdata.h"

#include "dbdriver.h"

OperatorsData::OperatorsData(const QString &pathToDB, QObject *parent) : QAbstractItemModel(parent), m_db_driver(new DBDriver(500, this))
{
    m_db_driver->open(pathToDB);
}

QVariant OperatorsData::data(const QModelIndex &index, int role) const
{
    QVariant result;

    if (index.isValid() && role == Qt::DisplayRole)
    {
        QSharedPointer<country_t> country = m_db_driver->get_country_by_id(index.internalId());

        if(country)
            result.setValue(country);
        else
        {
            int mcc = operator_t::mcc_from_id(index.internalId());
            QSharedPointer<country_t> country = m_db_driver->get_country_by_id(mcc);

            if(country)
            {
                QSharedPointer<operator_t> op = country->operator_by_id(index.internalId());

                if(op)
                    result.setValue(op);
            }
        }
    }

    return result;
}

Qt::ItemFlags OperatorsData::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    if(index.parent().isValid())
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;


    return QAbstractItemModel::flags(index);
}

QModelIndex OperatorsData::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex ret_val = QModelIndex();

    if (hasIndex(row, column, parent))
    {
        int countries_count = m_db_driver->get_countries_count();
        QSharedPointer<country_t> country = m_db_driver->get_country(row);

        if(!parent.isValid())
        {
            if(country && column == 0 && row < countries_count)
                ret_val = createIndex(row, column, country->get_id());
        }else
        {
            if(parent.column() == 0)
            {
                QSharedPointer<country_t> country = m_db_driver->get_country_by_id(parent.internalId());

                if(country && row < country->operators_count())
                {
                    QSharedPointer<operator_t> op = country->operators[row];
                    ret_val = createIndex(row, column, op->get_id());
                }
            }
        }
    }

    return ret_val;
}

QModelIndex OperatorsData::parent(const QModelIndex &index) const
{
    if (!index.isValid())
         return QModelIndex();

    QSharedPointer<country_t> country = m_db_driver->get_country_by_id(index.internalId());

    if(country)
        return QModelIndex();
    else
    {
        int mcc = operator_t::mcc_from_id(index.internalId());
        int index = m_db_driver->get_country_index_by_id(mcc);

        return createIndex(index, 0, mcc);
    }

    return QModelIndex();
}

int OperatorsData::rowCount(const QModelIndex &parent) const
{
    int ret_value = 0;

    if (!parent.isValid())
    {
        ret_value = m_db_driver->get_countries_count();
    }else
    {
        if(parent.column() == 0)
        {
            QSharedPointer<country_t> country = m_db_driver->get_country_by_id(parent.internalId());

            if(country)
                ret_value = country->operators_count();
        }
    }

    return ret_value;
}

int OperatorsData::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QSharedPointer<country_t> OperatorsData::get_country_by_id(int id) const
{
    return m_db_driver->get_country_by_id(id);
}

void OperatorsData::changeOperatorName(int mcc, int mnc, const QString &name)
{
    m_db_driver->changeOperatorName(mcc, mnc, name);

    emit requestRefresh();
}

void OperatorsData::createNewOperator(int mcc, int mnc, const QString &name)
{
    m_db_driver->createNewOperator(mcc, mnc, name);

    emit requestRebuild();
}
