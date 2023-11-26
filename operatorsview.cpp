#include "operatorsview.h"

#include "operatorsviewdelegates.h"

#include <QPushButton>

OperatorsView::OperatorsView(QWidget *parent) : QTreeView(parent), m_last_mcc(0), m_last_mnc(0)
{
    setHeaderHidden(true);
    setSelectionMode(QAbstractItemView::NoSelection);
    viewport()->setAttribute(Qt::WA_Hover);

    OperatorsViewDelegate* delegate = new OperatorsViewDelegate(this);

    setItemDelegate(delegate);

    actionButton = new QPushButton(this);
    actionButton->setVisible(false);
    actionButton->setText("+");
    actionButton->setStyleSheet("QPushButton {border: none;}");

    connect(delegate, SIGNAL(requestButtonInPosition(QRect,int,int)), this, SLOT(OnRequestButtonInPosition(QRect,int,int)));
    connect(delegate, SIGNAL(requestHideButton()), this, SLOT(OnRequestHideButton()));
    connect(actionButton, SIGNAL(clicked()), this, SLOT(OnActionButtonClick()));
}

void OperatorsView::operatorActionPressed(int mcc, int mnc)
{
    qDebug() << "MCC" << mcc << "MNC" << mnc;
}

void OperatorsView::OnRequestButtonInPosition(const QRect &pos, int mcc, int mnc)
{
    m_last_mcc = mcc;
    m_last_mnc = mnc;

    actionButton->resize(pos.size());
    actionButton->move(pos.topLeft());
    actionButton->setVisible(true);
}

void OperatorsView::OnRequestHideButton()
{
    if(!actionButton->underMouse())
        actionButton->setVisible(false);
}

void OperatorsView::OnActionButtonClick()
{
    operatorActionPressed(m_last_mcc, m_last_mnc);
}
