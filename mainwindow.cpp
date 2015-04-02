#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "select_path.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    form= new Select_path();
    connect(form,SIGNAL(send(QString)),ui->lineEdit,SLOT(setText(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    form->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    form->hide();
}
