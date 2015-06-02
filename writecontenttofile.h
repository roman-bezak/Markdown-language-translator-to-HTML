#ifndef WRITECONTENTTOFILE_H
#define WRITECONTENTTOFILE_H
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QTextDocumentWriter>


class WriteContentToFile: public QThread
{

public:

    QString file_path;

    WriteContentToFile(QString path)
    {
       file_path = path;
    }

    QString text;

    void run()
    {
            QFile file(file_path + "/bin/fromplaintext");
            file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out << text;
            file.close();
    }



};

#endif // WRITECONTENTTOFILE_H
