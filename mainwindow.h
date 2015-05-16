#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextDocumentWriter>

#include "options.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);

    ~MainWindow();



private slots:

    void fileOpen();
    void fileNew();
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    bool load(const QString &fileName);
    void reload_web_view();




private:

    bool maybeSave();
    void setFileName(const QString &fileName);

    //void init_app();


    Ui::MainWindow *ui;
    QString fileName;


    Options *options;

};

#endif // MAINWINDOW_H
