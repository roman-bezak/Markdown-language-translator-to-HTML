#include "select_path.h"
#include "ui_select_path.h"

Select_path::Select_path(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Select_path)
{
    ui->setupUi(this);

    //connect(ui->,SIGNAL(o))
}

Select_path::~Select_path()
{
    delete ui;
}

//void Select_path::send(QString str);


void Select_path::on_pushButton_clicked()
{
    emit send(ui->lineEdit->text());
}
