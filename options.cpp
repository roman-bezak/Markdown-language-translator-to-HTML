#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    for(int i = 6; i <= 18; i++)
        ui->sizeComboBox->addItem(QString::number(i));

    this->setWindowIcon(QIcon("C://Qt/Qt5.3.2/Tools/QtCreator/bin/build-MARKDOWN_COMPILER-Desktop_Qt_5_3_MinGW_32bit-Debug/debug/images/main_icon.png"));
    //font =


}

Options::~Options()
{
    delete ui;
}
