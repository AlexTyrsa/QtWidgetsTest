#include "operatorsviewdelegates.h"

#include <QApplication>

#include "datatypes.h"
#include "iconsloader.h"

OperatorsViewDelegate::OperatorsViewDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void OperatorsViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid())
    {
        if(!index.parent().isValid())
        {
            QSharedPointer<country_t> data = qvariant_cast<QSharedPointer<country_t>>(index.data());

            if(data)
            {
                QPixmap icon = IconsLoader::get()->iconFromCountryCode(data->code);

                QApplication::style()->drawItemPixmap(painter, option.rect, option.displayAlignment, icon);
                QApplication::style()->drawItemText(painter, option.rect.translated(icon.width() + 5, 0), option.displayAlignment, option.palette, true, data->name);
            }
        }else
        {
            QSharedPointer<operator_t> data = qvariant_cast<QSharedPointer<operator_t>>(index.data());

            if(data)
            {
                QPixmap icon = IconsLoader::get()->iconFromMCCMNC(data->mcc, data->mnc);
                QString text = data->name + " (" + QString::number(data->mcc) + ", " + QString::number(data->mnc) + ")";

                QApplication::style()->drawItemPixmap(painter, option.rect, option.displayAlignment, icon);
                QApplication::style()->drawItemText(painter, option.rect.translated(icon.width() + 5, 0), option.displayAlignment, option.palette, true, text);
            }
        }
    }
}
