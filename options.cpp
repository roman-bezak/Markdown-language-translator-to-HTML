#include "options.h"
#include "ui_options.h"
#include <QCloseEvent>


Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);

    for(int i = 6; i <= 18; i++)
        ui->sizeComboBox->addItem(QString::number(i));

    ui->sizeComboBox->setCurrentIndex(4);

    this->setWindowIcon(QIcon("C://Qt/Qt5.3.2/Tools/QtCreator/bin/build-MARKDOWN_COMPILER-Desktop_Qt_5_3_MinGW_32bit-Debug/debug/images/main_icon.png"));


    font.setFamily("MS Shell Dlg 2");
    font.setPointSize(10);

}

Options::~Options()
{
    delete ui;
}

void Options::closeEvent(QCloseEvent *e)
{
    ui->sizeComboBox->setCurrentText(QString::number(font.pointSize()));
    ui->fontComboBox->setCurrentFont(font);
    e->accept();
}

void Options::on_buttonBox_rejected()
{
    ui->sizeComboBox->setCurrentText(QString::number(font.pointSize()));
    ui->fontComboBox->setCurrentFont(font);
    this->hide();
}

void Options::on_buttonBox_accepted()
{
    font = ui->fontComboBox->currentFont();
    font.setPointSize(ui->sizeComboBox->currentText().toInt());

    emit change_options(font);

    this->hide();
}
