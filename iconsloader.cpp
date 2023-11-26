#include "iconsloader.h"

#include <QApplication>
#include <QFile>

QSharedPointer<IconsLoader> IconsLoader::s_inst = QSharedPointer<IconsLoader>();

QSharedPointer<IconsLoader> IconsLoader::get()
{
    if(!s_inst)
        s_inst.reset(new IconsLoader());

    return s_inst;
}

QPixmap IconsLoader::iconFromCountryCode(const QString &in_code)
{
    if(!is_cached(in_code))
    {
        QString path = getIconsCountriesPath() + in_code + ".png";

        if(QFile::exists(path))
            load_to_cache(in_code, path);
        else
            return mDefaultCountryIcon;
    }

    return get_from_cache(in_code);
}

QPixmap IconsLoader::iconFromMCCMNC(int in_mcc, int in_mnc)
{
    QString id = QString::number(in_mcc) + "_" + QString::number(in_mnc);

    if(!is_cached(id))
    {
        QString path = getIconsOperatorsPath() + id + ".png";

        if(QFile::exists(path))
            load_to_cache(id, path);
        else
            return mDefaultOperatorIcon;
    }

    return get_from_cache(id);
}

QString IconsLoader::getIconsCountriesPath() const
{
    return QApplication::applicationDirPath() + RESOURCES_PATH + ICONS_COUNTRIES_PATH;
}

QString IconsLoader::getIconsOperatorsPath() const
{
    return QApplication::applicationDirPath() + RESOURCES_PATH + ICONS_OPERATORS_PATH;
}

QPixmap IconsLoader::getDefaultCountryIcon() const
{
    return mDefaultCountryIcon;
}

QPixmap IconsLoader::getDefaultOperatorIcon() const
{
    return mDefaultOperatorIcon;
}

IconsLoader::IconsLoader()
{
    mDefaultCountryIcon = QPixmap(getIconsCountriesPath() + "NONE.png");
    mDefaultOperatorIcon = QPixmap(getIconsOperatorsPath() + "NONE.png");
}

bool IconsLoader::is_cached(const QString &id) const
{
    return mIconsCache.contains(id);
}

QPixmap IconsLoader::get_from_cache(const QString &id) const
{
    return mIconsCache[id];
}

void IconsLoader::load_to_cache(const QString &id, const QString &path)
{
    mIconsCache[id] = QPixmap(path);
}
