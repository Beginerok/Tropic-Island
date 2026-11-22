#include "mainwindow.h"

#include <QApplication>

#include <QWebEngineView>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWebEngineView view;
    view.load(QUrl("https://beginerok.github.io"));
    view.resize(1024, 768);
    view.show();
    return a.exec();
}
