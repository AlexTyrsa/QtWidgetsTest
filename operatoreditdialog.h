#pragma once

#include <QDialog>

#include <QLabel>
#include <QLineEdit>

class QAbstractItemModel;
class OperatorsData;

class OperatorEditDialog : public QDialog
{
    Q_OBJECT

public:
    OperatorEditDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void setData(OperatorsData* in_data);
    void setValues(int mcc, int mnc);

    QString getName() const;
    int getMCC() const;
    int getMNC() const;

    static void startEdit(int mcc, int mnc, QAbstractItemModel* model);
    static void startCreate(QAbstractItemModel* model);

private:
    OperatorsData* m_data;

    QLabel* operatorIcon;
    QLabel* countryIcon;
    QLineEdit* nameEdit;
    QLineEdit* mccEdit;
    QLineEdit* mncEdit;

};
