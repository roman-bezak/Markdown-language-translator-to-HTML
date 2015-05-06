#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileIconProvider>
#include <QIcon>
#include <QFileInfo>
#include <QTextBlock>
#include <QPainter>
#include <QDebug>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag=0;
    //ui->action->setCheckable(false);
    connect(ui->action,SIGNAL(triggered()),this,SLOT(fileOpen()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{

    QThread *p;
    p = new QThread();
    p->start();
    for(int i=0;i<5;i++)
    {
        qDebug() <<flag;
    }
    flag++;
    p->exit();
}


