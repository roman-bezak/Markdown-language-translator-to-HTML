#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFileIconProvider>
#include <QIcon>
#include <QFileInfo>
#include <QTextBlock>
#include <QDebug>
#include <QThread>
#include <QTextDocumentWriter>
#include <QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->file_new,SIGNAL(triggered()),this,SLOT(fileNew()));
    connect(ui->file_open,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->file_save,SIGNAL(triggered()),this,SLOT(fileSave()));
    connect(ui->file_save_as,SIGNAL(triggered()),this,SLOT(fileSaveAs()));
    connect(ui->file_print,SIGNAL(triggered()),this,SLOT(filePrint()));


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
void MainWindow::fileNew()
{
    if (maybeSave())
    {
        //wordCountLabel->setText("");
        //wordCountLabel->setToolTip("");
        ui->plainTextEdit->clear();
       //ui->plainTextEdit->resetHighlighting();
        ui->webView->setHtml(QString());
        //ui->htmlSourceTextEdit->clear();
        setFileName(QString());
    }
}
bool MainWindow::fileSave()
{
    // файл  без имени
    if (fileName.isEmpty()) {
        return fileSaveAs();
    }

    QTextDocumentWriter writer(fileName, "plaintext");
    bool success = writer.write(ui->plainTextEdit->document());

    if (success)
    {
        ui->plainTextEdit->document()->setModified(false);
        setWindowModified(false);
    }

    return success;
}
bool MainWindow::fileSaveAs()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Save as..."), QString(),
                                              tr("Markdown Files (*.markdown *.md);;All Files (*)"));
    if (name.isEmpty()) {
        return false;
    }

    //к файлам без расширения по дефолту добавляем расширение (.md)
    if (QFileInfo(name).suffix().isEmpty()) {
        name.append(".md");
    }

    setFileName(name);
    return fileSave();
}
void MainWindow::filePrint()
{
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    dlg->setWindowTitle(tr("Print Document"));

    if (ui->webView->hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);

    if (dlg->exec() == QDialog::Accepted)
        ui->webView->print(&printer);

    delete dlg;
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
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;

    return true;
}




