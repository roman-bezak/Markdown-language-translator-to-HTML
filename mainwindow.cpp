#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileexplorerwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FileExplorerWidget *ss;

    ss = new FileExplorerWidget();
    ss->show();
   // ui->centralWidget->setContentsMargins(-10,-8,-8,-8);

}

MainWindow::~MainWindow()
{
    delete ui;
}

