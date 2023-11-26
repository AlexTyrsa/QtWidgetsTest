#pragma once

#include <QString>
#include <QSharedPointer>
#include <QVector>

struct operator_t
{
    operator_t();
    operator_t(int in_mcc, int in_mnc, const QString& in_name = QString());

    bool is_valid() const;
    bool is_valid(int for_mcc) const;
    QString to_string() const;
    int get_id() const;
    bool check_id(int id) const;

    static int mcc_from_id(int id);

    int mcc;
    int mnc;
    QString name;

};

struct country_t
{
    country_t();
    country_t(int in_mcc, const QString& in_code = QString(), const QString& in_name = QString());

    bool is_valid() const;
    int  operators_count() const;
    QString to_string() const;
    int get_id() const;
    bool check_id(int id) const;
    QSharedPointer<operator_t> operator_by_id(int id) const;
    QSharedPointer<operator_t> operator_by_mnc(int mnc) const;

    int     mcc;
    QString code;
    QString name;

    QVector<QSharedPointer<operator_t>> operators;
};
