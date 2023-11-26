#pragma once

#include <QStyledItemDelegate>

class OperatorsViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    OperatorsViewDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};
