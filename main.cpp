#include "mainwindow.h"

#include "operatorsview.h"
#include "operatorsdata.h"

#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow* w = new MainWindow();
    OperatorsView* view = new OperatorsView(w);

    w->resize(800, 600);
    w->setCentralWidget(view);

    OperatorsData* data = new OperatorsData(QApplication::applicationDirPath() + RESOURCES_PATH + DB_FILE_NAME);
    view->setModel(data);

    w->show();

    return a.exec();
}
