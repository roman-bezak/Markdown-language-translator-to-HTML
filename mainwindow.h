#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>


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

private:

    bool maybeSave();
    void setFileName(const QString &fileName);


    Ui::MainWindow *ui;
    QString fileName;
    HtmlPreviewGenerator* generator;
    HtmlHighlighter *htmlHighlighter;

};

#endif // MAINWINDOW_H
