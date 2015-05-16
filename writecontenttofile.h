#ifndef WRITECONTENTTOFILE_H
#define WRITECONTENTTOFILE_H
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QTextDocumentWriter>


class WriteContentToFile: public QThread
{

public:

    WriteContentToFile();
    QString text;

    void run()
    {
            QFile file("file.txt");
            file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out << text;
            file.close();
    }



};

#endif // WRITECONTENTTOFILE_H
