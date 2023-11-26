#pragma once

#include <QTreeView>

class QPushButton;

class OperatorsView: public QTreeView
{
    Q_OBJECT

public:
    OperatorsView(QWidget *parent = nullptr);

private:
    QPushButton* actionButton;

public slots:
    virtual void operatorActionPressed(int mcc, int mnc);       //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

private slots:
    void OnRequestButtonInPosition(const QRect& pos, int mcc, int mnc);
    void OnRequestHideButton();
    void OnActionButtonClick();

private:
    int m_last_mcc;
    int m_last_mnc;

};
