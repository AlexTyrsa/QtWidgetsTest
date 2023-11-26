#include "operatoreditdialog.h"

#include "iconsloader.h"
#include "operatorsdata.h"
#include "datatypes.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QIntValidator>

OperatorEditDialog::OperatorEditDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f), m_data(nullptr)
{
    QFormLayout* dialog = new QFormLayout(this);

    QDialogButtonBox *btn_box = new QDialogButtonBox(this);
    btn_box->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel);

    connect(btn_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btn_box, &QDialogButtonBox::rejected, this, &QDialog::reject);

    operatorIcon = new QLabel(this);

    QHBoxLayout* header = new QHBoxLayout();
    header->addWidget(operatorIcon, Qt::AlignLeft);
    header->addWidget(new QLabel(tr("Operator Editor")), Qt::AlignHCenter);

    nameEdit = new QLineEdit(this);
    mccEdit = new QLineEdit(this);
    mncEdit = new QLineEdit(this);
    countryIcon = new QLabel(this);

    mccEdit->setValidator(new QIntValidator(0, 9999, this));
    mncEdit->setValidator(new QIntValidator(0, 9999, this));

    QHBoxLayout* mccL = new QHBoxLayout();

    mccL->addWidget(mccEdit);
    mccL->addWidget(countryIcon, Qt::AlignRight);

    dialog->addRow(header);
    dialog->addRow(tr("Name"), nameEdit);
    dialog->addRow(tr("MCC"), mccL);
    dialog->addRow(tr("MNC"), mncEdit);
    dialog->addWidget(btn_box);

    this->setLayout(dialog);
}

void OperatorEditDialog::setData(OperatorsData *in_data)
{
    m_data = in_data;
}

void OperatorEditDialog::setValues(int mcc, int mnc)
{
    if(m_data)
    {
        QSharedPointer<country_t> country = m_data->get_country_by_id(mcc);

        if(country)
        {
            QSharedPointer<operator_t> op = country->operator_by_mnc(mnc);

            if(op)
            {
                nameEdit->setText(op->name);
                mccEdit->setText(QString::number(mcc));
                mccEdit->setReadOnly(true);
                mncEdit->setText(QString::number(mnc));
                mncEdit->setReadOnly(true);

                operatorIcon->setPixmap(IconsLoader::get()->iconFromMCCMNC(mcc, mnc));
                countryIcon->setPixmap(IconsLoader::get()->iconFromCountryCode(country->code));
            }
        }
    }
}

QString OperatorEditDialog::getName() const
{
    return nameEdit->text();
}

int OperatorEditDialog::getMCC() const
{
    return mccEdit->text().toInt();
}

int OperatorEditDialog::getMNC() const
{
    return mncEdit->text().toInt();
}

void OperatorEditDialog::startEdit(int mcc, int mnc, QAbstractItemModel* model)
{
    OperatorEditDialog* dialog = new OperatorEditDialog();
    OperatorsData* data = qobject_cast<OperatorsData*>(model);

    if(data)
    {
        dialog->setData(data);
        dialog->setValues(mcc, mnc);

        if(dialog->exec() == QDialog::Accepted)
        {
            data->changeOperatorName(mcc, mnc, dialog->getName());
        }
    }

    delete dialog;
}

void OperatorEditDialog::startCreate(QAbstractItemModel* model)
{
    OperatorEditDialog* dialog = new OperatorEditDialog();
    OperatorsData* data = qobject_cast<OperatorsData*>(model);

    if(data)
    {
        dialog->setData(data);

        if(dialog->exec() == QDialog::Accepted)
        {
            data->createNewOperator(dialog->getMCC(), dialog->getMNC(), dialog->getName());
        }
    }

    delete dialog;
}
