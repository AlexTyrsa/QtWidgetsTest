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

    w->show();

    return a.exec();
}
