#ifndef RELOADWEBVIEW_H
#define RELOADWEBVIEW_H
#include <QThread>
#include <QWebView>

class ReloadWebView: public QThread
{
public:

    ReloadWebView();

signals:

void signal();

public:

    void run()
    {
        //qwe.load(QUrl("file:///D://result.html"));
    }


};

#endif // RELOADWEBVIEW_H
