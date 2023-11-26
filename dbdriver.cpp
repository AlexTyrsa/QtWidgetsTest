#include "dbdriver.h"

#include <QSqlQuery>
#include <QSqlRecord>

#include <algorithm>

DBDriver::DBDriver(int in_cache_size, QObject *parent) : QObject(parent), m_cache_size(in_cache_size), m_cache_index(0)
{

}

bool DBDriver::open(const QString &pathToDB)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(pathToDB);

    return m_db.open();
}

int DBDriver::get_countries_count() const
{
    QSqlQuery a_query;

    if(a_query.exec("SELECT COUNT(mcc) FROM countries WHERE mcc != 0"))
    {
        if(a_query.next())
            return a_query.value(0).toInt();
    }

    return 0;
}

QSharedPointer<country_t> DBDriver::get_country(int index) const
{
    if(!is_cached(index))
        cache_from_index(index);

    return get_from_cache(index);
}

QSharedPointer<country_t> DBDriver::get_country_by_id(int id) const
{
    int countries_count = get_countries_count();

    for(int i = 0; i < countries_count; ++i)
    {
        QSharedPointer<country_t> country = get_country(i);

        if(country && country->check_id(id))
            return country;
    }

    return QSharedPointer<country_t>();
}

int DBDriver::get_country_index_by_id(int id) const
{
    int countries_count = get_countries_count();

    for(int i = 0; i < countries_count; ++i)
    {
        QSharedPointer<country_t> country = get_country(i);

        if(country && country->check_id(id))
            return i;
    }

    return -1;
}

QVector<QSharedPointer<operator_t>> DBDriver::get_operators(int mcc) const
{
    QSqlQuery a_query;
    QVector<QSharedPointer<operator_t>> ret_value;

    if(a_query.exec("SELECT * FROM operators WHERE mcc = " + QString::number(mcc)))
    {
        QSqlRecord rec = a_query.record();

        while (a_query.next())
        {
            int mcc = a_query.value(rec.indexOf("mcc")).toInt();
            int mnc = a_query.value(rec.indexOf("mnc")).toInt();
            QString name = a_query.value(rec.indexOf("name")).toString();

            ret_value.push_back(QSharedPointer<operator_t>(new operator_t(mcc, mnc, name)));
        }
    }

    return ret_value;
}

void DBDriver::fill_operators(QSharedPointer<country_t> country) const
{
    if(country)
        country->operators = get_operators(country->mcc);
}

void DBDriver::changeOperatorName(int mcc, int mnc, const QString &name)
{
    QSqlQuery a_query;

    a_query.exec("UPDATE operators SET name = \"" + name + "\" WHERE mcc = " + QString::number(mcc) + " AND mnc = " + QString::number(mnc));

    drop_cache();
}

void DBDriver::createNewOperator(int mcc, int mnc, const QString &name)
{

}

bool DBDriver::cache_is_empty() const
{
    return m_cache.empty();
}

bool DBDriver::is_cached(int index) const
{
    if(!cache_is_empty())
        return index >= m_cache_index && index < m_cache_index + m_cache_size;

    return false;
}

QSharedPointer<country_t> DBDriver::get_from_cache(int index) const
{
    if(is_cached(index))
    {
        int idx = index - m_cache_index;

        if(idx >= 0 && idx < m_cache.size())
            return m_cache[idx];
    }

    return QSharedPointer<country_t>();
}

void DBDriver::cache_from_index(int index) const
{
    QSqlQuery a_query;

    m_cache.clear();
    m_cache_index = index;

    if(a_query.exec("SELECT * FROM countries LIMIT " + QString::number(m_cache_size) + " OFFSET " + QString::number(m_cache_index)))
    {
        QSqlRecord rec = a_query.record();

        while (a_query.next())
        {
            int mcc = a_query.value(rec.indexOf("mcc")).toInt();
            QString code = a_query.value(rec.indexOf("code")).toString();
            QString name = a_query.value(rec.indexOf("name")).toString();

            m_cache.push_back(QSharedPointer<country_t>(new country_t(mcc, code, name)));
        }
    }

    std::for_each(m_cache.begin(), m_cache.end(), [this](QSharedPointer<country_t> in_country)->void
    {
        fill_operators(in_country);
    });
}

void DBDriver::drop_cache()
{
    m_cache.clear();
    m_cache_index = 0;
}
