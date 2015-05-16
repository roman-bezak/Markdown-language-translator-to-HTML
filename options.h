#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QFont>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:

    Options(QWidget *parent = 0);
    ~Options();

    QFont font;
    int font_size;

//private slots:

//    void clear_options();

//signals:

    //void change_options();


    Ui::Options *ui;



};

#endif // OPTIONS_H
