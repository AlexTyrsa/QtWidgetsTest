#include "mainwindow.h"

#include "operatorsview.h"
#include "operatorsdata.h"
#include "datatypes.h"

#include <QApplication>
#include <QMetaType>
#include <QtSql>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    qRegisterMetaType<QSharedPointer<operator_t>>("shared_operator_t");
    qRegisterMetaType<QSharedPointer<country_t>>("shared_country_t");
    QMetaType::registerConverter<QSharedPointer<operator_t>, QString>([](QSharedPointer<operator_t> op)->QString
    {
        return op->to_string();
    });
    QMetaType::registerConverter<QSharedPointer<country_t>, QString>([](QSharedPointer<country_t> cn)->QString
    {
        return cn->to_string();
    });

    QMainWindow* w = new MainWindow();
    OperatorsView* view = new OperatorsView(w);

    w->resize(800, 600);
    w->setCentralWidget(view);

    OperatorsData* data = new OperatorsData(QApplication::applicationDirPath() + RESOURCES_PATH + DB_FILE_NAME);
    view->setModel(data);

    w->show();

    return a.exec();
}
