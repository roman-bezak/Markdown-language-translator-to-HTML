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


    connect(ui->action,SIGNAL(triggered()),this,SLOT(fileOpen()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{

    if (maybeSave()) {
        QString name = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                                    QString(), tr("Markdown Files (*.markdown *.md);;All Files (*)"));
        if (!name.isEmpty()) {
            load(name);
        }
    }
}

bool MainWindow::load(const QString &fileName)
{
    if (!QFile::exists(fileName)) {
        return false;
    }

    //открываем файл
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return false;

    //чтаем содержимое файла
    QByteArray content = file.readAll();
    QString text = QString::fromUtf8(content);

    //ui->plainTextEdit->resetHighlighting();//Error
    //добавляе на виджет текст
    ui->plainTextEdit->setPlainText(text);

    //сохраняем содержимое файла
    setFileName(fileName);

    return true;
}

void MainWindow::setFileName(const QString &fileName)
{
    this->fileName = fileName;

    ui->plainTextEdit->document()->setModified(false);
    setWindowModified(false);


    QString shownName = fileName;

    if (shownName.isEmpty()) {

        shownName = tr("untitled.md");              //fix
    }

    setWindowFilePath(shownName);                   //fix
}



bool MainWindow::maybeSave()
{
    if (!ui->plainTextEdit->document()->isModified())
        return true;

    if (fileName.startsWith(QLatin1String(":/")))
        return true;

    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Save Changes"),

                               tr("The document has been modified.<br>"
                                  "Do you want to save your changes?"),

                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save)
        return true;            //will be fixed ...fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;

    return true;
}




