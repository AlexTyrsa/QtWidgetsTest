#include "operatorsview.h"

#include "operatorsviewdelegates.h"

OperatorsView::OperatorsView(QWidget *parent) : QTreeView(parent)
{
    setHeaderHidden(true);

    setItemDelegate(new OperatorsViewDelegate(this));
}
