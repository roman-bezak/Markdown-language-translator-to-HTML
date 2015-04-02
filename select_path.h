#ifndef SELECT_PATH_H
#define SELECT_PATH_H

#include <QWidget>

namespace Ui {
class Select_path;
}

class Select_path : public QWidget
{
    Q_OBJECT

public:

    explicit Select_path(QWidget *parent = 0);
    ~Select_path();

    Ui::Select_path *ui;

public:
signals:
    void send(QString str);


public slots:
    void on_pushButton_clicked();
};

#endif // SELECT_PATH_H
