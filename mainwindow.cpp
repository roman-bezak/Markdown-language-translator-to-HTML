#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "exportpdfdialog.h"


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
#include <QProcess>
#include <QUrl>
#include <QTimer>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    options(new Options(this))
{
    ui->setupUi(this);
    init_app();
}

MainWindow::~MainWindow()
{ 
    delete ui;
}


void MainWindow::init_app()
{
    ui->pravka_otmenit->setIcon(QIcon(QCoreApplication::applicationDirPath()+"/icons/main_icon.png"));

    wordCountLabel = new QLabel(this);
    wordCountLabel->setAlignment(Qt::AlignCenter);
    wordCountLabel->setText("0 words");


    ui->statusBar->addPermanentWidget(wordCountLabel,2);


    translator = new QProcess();
    QStringList arguments;
    arguments << QCoreApplication::applicationDirPath() + "/bin/fromplaintext" << QCoreApplication::applicationDirPath() + "/bin/resulthtml.html";
    translator -> start( QCoreApplication::applicationDirPath() + "/md_translator.exe", arguments );




    ui->webView->load(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/bin/resulthtml.html"));





    connect(ui->file_new,SIGNAL(triggered()),this,SLOT(fileNew()));
    connect(ui->file_open,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->file_save,SIGNAL(triggered()),this,SLOT(fileSave()));
    connect(ui->file_save_as,SIGNAL(triggered()),this,SLOT(fileSaveAs()));
    connect(ui->file_print,SIGNAL(triggered()),this,SLOT(filePrint()));
    connect(ui->editor_options,SIGNAL(triggered()),options,SLOT(show()));
    connect(ui->plainTextEdit,SIGNAL(textChanged()),this,SLOT(reload_web_view()));
    connect(options,SIGNAL(change_options(QFont)),this,SLOT(set_options(QFont)));
    connect(ui->vid_fullscrean,SIGNAL(changed()),this,SLOT(set_full_screan()));
    connect(ui->file_in_PDF,SIGNAL(triggered()),this,SLOT(export_to_PDF()));
    connect(ui->file_in_HTML,SIGNAL(triggered()),this,SLOT(export_to_HTML()));
    connect(ui->pravka_otmenit,SIGNAL(triggered()),this,SLOT(editUndo()));
    connect(ui->pravka_povtorit,SIGNAL(triggered()),this,SLOT(editRedo()));
    connect(ui->plainTextEdit,SIGNAL(textChanged()),this,SLOT(update_words_counter()));



    //plain_text default
    ui->plainTextEdit->setFont(QFont("MS Shell Dlg 2",10));

}

void MainWindow::closeEvent(QCloseEvent *e)
{
    delete translator;
    e->accept();
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
        wordCountLabel->setText("");
        wordCountLabel->setToolTip("");
        ui->plainTextEdit->clear();
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

void MainWindow::editUndo()
{
    if (ui->plainTextEdit->document()->isUndoAvailable()) {
        ui->plainTextEdit->document()->undo();
    }
}

void MainWindow::editRedo()
{
    if (ui->plainTextEdit->document()->isRedoAvailable()) {
        ui->plainTextEdit->document()->redo();
    }
}
void MainWindow::reload_web_view()
{
   //ui->webView->reload(QUrl("file:///" + QCoreApplication::applicationDirPath() + "/bin/resulthtml.html"));
    emit ui->webView->reload();

}

void MainWindow::set_full_screan()
{
    if (ui->vid_fullscrean->isChecked()) {
        showFullScreen();
    } else {
        showNormal();
    }
}

void MainWindow::update_words_counter()
{
    if (wordCountLabel)
    {
        int words = ui->plainTextEdit->countWords();
        int lines = ui->plainTextEdit->document()->lineCount();
        int chars = ui->plainTextEdit->document()->characterCount();
        wordCountLabel->setText(tr("%1 words").arg(words));
        wordCountLabel->setToolTip(tr("Lines: %1  Words: %2  Characters: %3").arg(lines).arg(words).arg(chars));
    }
}

void MainWindow::set_options(QFont font)
{
    ui->plainTextEdit->setFont(font);
}

void MainWindow::export_to_HTML()
{
    QString name = QFileDialog::getSaveFileName(this, tr("Сохранить"), QString(),
                                              tr("HTML files (*.html *.htm);;All Files (*)"));

    QFile::copy(QCoreApplication::applicationDirPath() + "/bin/resulthtml.html",name);

}

void MainWindow::export_to_PDF()
{
    ExportPdfDialog dialog(fileName);
    if (dialog.exec() == QDialog::Accepted) {
        ui->webView->print(dialog.printer());
    }
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

    ret = QMessageBox::warning(this, tr("Сохранение изменений"),

                               tr("Этот документ был изменён.<br>"
                                  "Хотите сохранить свои изменения?"),

                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;

    return true;
}


