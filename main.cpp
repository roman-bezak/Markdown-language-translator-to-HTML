#include "mainwindow.h"
#include <QApplication>
#include <QIcon>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowIcon(QIcon("C://Qt/Qt5.3.2/Tools/QtCreator/bin/build-MARKDOWN_COMPILER-Desktop_Qt_5_3_MinGW_32bit-Debug/debug/images/main_icon.png"));

    w.show();


    return a.exec();
}
