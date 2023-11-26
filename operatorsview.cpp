#include "operatorsview.h"

#include "operatorsviewdelegates.h"
#include "operatoreditdialog.h"

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
    connect(delegate, SIGNAL(editRequest(int,int)), this, SLOT(OnEditRequest(int,int)));
    connect(actionButton, SIGNAL(clicked()), this, SLOT(OnActionButtonClick()));
}

void OperatorsView::setModel(QAbstractItemModel *model)
{
    connect(model, SIGNAL(requestRefresh()), this, SLOT(OnRequestRefresh()));
    connect(model, SIGNAL(requestRebuild()), this, SLOT(OnRequestRebuild()));

    QTreeView::setModel(model);
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

void OperatorsView::OnEditRequest(int mcc, int mnc)
{
    OperatorEditDialog::startEdit(mcc, mnc, model());
}

void OperatorsView::OnCreateNewRequest()
{
    OperatorEditDialog::startCreate(model());
}

void OperatorsView::OnRequestRefresh()
{
    repaint();
}

void OperatorsView::OnRequestRebuild()
{

}
