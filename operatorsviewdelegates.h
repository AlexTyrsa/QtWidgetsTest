#pragma once

#include <QStyledItemDelegate>

class OperatorsViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    OperatorsViewDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

     QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:
    void requestButtonInPosition(const QRect& pos, int mcc, int mnc) const;
    void requestHideButton() const;
    void editRequest(int mcc, int mnc) const;

};
