#pragma once

#include <QSharedPointer>
#include <QPixmap>
#include <QMap>

class IconsLoader
{
public:
    static QSharedPointer<IconsLoader> get();

    QPixmap iconFromCountryCode(const QString& in_code);
    QPixmap iconFromMCCMNC(int in_mcc, int in_mnc);

    QString getIconsCountriesPath() const;
    QString getIconsOperatorsPath() const;

private:
    IconsLoader();

    bool is_cached(const QString& id) const;
    QPixmap get_from_cache(const QString& id) const;
    void load_to_cache(const QString& id, const QString& path);

private:
    QPixmap mDefaultCountryIcon;
    QPixmap mDefaultOperatorIcon;

    QMap<QString, QPixmap> mIconsCache;

private:
    static QSharedPointer<IconsLoader> s_inst;

};
