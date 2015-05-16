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
    Ui::Options *ui;

    void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;

signals:

    void change_options(QFont);

public:




private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // OPTIONS_H
