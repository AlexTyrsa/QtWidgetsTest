#include "datatypes.h"

operator_t::operator_t() : mcc(0), mnc(0)
{

}

operator_t::operator_t(int in_mcc, int in_mnc, const QString &in_name) : mcc(in_mcc), mnc(in_mnc), name(in_name)
{

}

bool operator_t::is_valid() const
{
    return mcc != 0 && mnc != 0;
}

bool operator_t::is_valid(int for_mcc) const
{
    return mcc == for_mcc && is_valid();
}

QString operator_t::to_string() const
{
    return QString("MCC(") + QString::number(mcc) + ") MNC(" + QString::number(mnc) + ") " + name;
}

int operator_t::get_id() const
{
    return (mnc << 16) + mcc;
}

bool operator_t::check_id(int id) const
{
    int nmcc = id & 0xFFFF;
    int nmnc = id >> 16;

    return nmcc == mcc && nmnc == mnc;
}

int operator_t::mcc_from_id(int id)
{
    int nmcc = id & 0xFFFF;

    return nmcc;
}

country_t::country_t() : mcc(0)
{

}

country_t::country_t(int in_mcc, const QString &in_code, const QString &in_name) : mcc(in_mcc), code(in_code), name(in_name)
{

}

bool country_t::is_valid() const
{
    return mcc != 0;
}

int country_t::operators_count() const
{
    return operators.size();
}

QString country_t::to_string() const
{
    return QString("MCC(") + QString::number(mcc) + ") " + code + " " + name;
}

int country_t::get_id() const
{
    return mcc;
}

bool country_t::check_id(int id) const
{
    int nmcc = id & 0xFFFF;
    int nmnc = id >> 16;

    return nmcc == mcc && nmnc == 0;
}

QSharedPointer<operator_t> country_t::operator_by_id(int id) const
{
    for(QVector<QSharedPointer<operator_t>>::const_iterator i = operators.cbegin(); i != operators.cend(); ++i)
    {
        if((*i)->check_id(id))
            return *i;
    }

    return QSharedPointer<operator_t>();
}

QSharedPointer<operator_t> country_t::operator_by_mnc(int mnc) const
{
    for(QVector<QSharedPointer<operator_t>>::const_iterator i = operators.cbegin(); i != operators.cend(); ++i)
    {
        if((*i)->mnc == mnc)
            return *i;
    }

    return QSharedPointer<operator_t>();
}
