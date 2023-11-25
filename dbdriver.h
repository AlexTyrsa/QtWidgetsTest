#pragma once

#include "datatypes.h"

#include <QObject>
#include <QSqlDatabase>

class DBDriver : public QObject
{
    Q_OBJECT

public:
    DBDriver(int in_cache_size = 10, QObject *parent = nullptr);

    bool open(const QString &pathToDB);

    int get_countries_count() const;
    QSharedPointer<country_t> get_country(int index) const;
    QSharedPointer<country_t> get_country_by_id(int id) const;
    int get_country_index_by_id(int id) const;
    QVector<QSharedPointer<operator_t>> get_operators(int mcc) const;
    void fill_operators(QSharedPointer<country_t> country) const;

private:
    bool cache_is_empty() const;
    bool is_cached(int index) const;
    QSharedPointer<country_t> get_from_cache(int index) const;
    void cache_from_index(int index) const;

private:
    QSqlDatabase                               m_db;
    mutable QVector<QSharedPointer<country_t>> m_cache;
    const int                                  m_cache_size;
    mutable int                                m_cache_index;

};
