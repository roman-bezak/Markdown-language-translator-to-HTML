#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextDocumentWriter>
#include <QFont>
#include <QProcess>
#include <QLabel>



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
    void editUndo();
    void editRedo();
    void reload_web_view();

    void set_full_screan();
    void update_words_counter();
    void set_options(QFont font);
    void export_to_HTML();
    void export_to_PDF();



private:

    bool maybeSave();
    void setFileName(const QString &fileName);
    void init_app();
    void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;


    Ui::MainWindow *ui;
    QString fileName;

    QProcess *translator;
    Options *options;

    QLabel *wordCountLabel;
    QLabel *styleLabel;

};


#endif // MAINWINDOW_H
