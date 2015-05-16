#ifndef MdEditor_H
 #define MdEditor_H

 #include <QPlainTextEdit>
 #include <QObject>
 #include <QThread>
 #include "writecontenttofile.h"

 class QPaintEvent;
 class QResizeEvent;
 class QSize;
 class QWidget;

 class LineNumberArea;


 class MdEditor : public QPlainTextEdit
 {
     Q_OBJECT

 public:

     MdEditor(QWidget *parent = 0);

     void lineNumberAreaPaintEvent(QPaintEvent *event);
     int lineNumberAreaWidth();


 protected:
     void resizeEvent(QResizeEvent *event);


 private slots:

     void save();
     void updateLineNumberAreaWidth(int newBlockCount);
     void highlightCurrentLine();
     void updateLineNumberArea(const QRect &, int);


 private:

     QWidget *lineNumberArea;


 };


 class LineNumberArea : public QWidget
 {
 public:
     LineNumberArea(MdEditor *editor) : QWidget(editor) {
         codeditor = editor;
     }

     QSize sizeHint() const {
         return QSize(codeditor->lineNumberAreaWidth(), 0);
     }

 protected:
     void paintEvent(QPaintEvent *event) {
         codeditor->lineNumberAreaPaintEvent(event);
     }

 private:

     MdEditor *codeditor;

 };


 #endif
