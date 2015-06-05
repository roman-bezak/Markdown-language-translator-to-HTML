#include <QtGui>

#include "mdeditor.h"
#include "writecontenttofile.h"
#include "QThread"


 MdEditor::MdEditor(QWidget *parent) : QPlainTextEdit(parent)
 {
     lineNumberArea = new LineNumberArea(this);

     connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
     connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
     connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
     connect(this, SIGNAL(textChanged()), this, SLOT(save()));

     updateLineNumberAreaWidth(0);
     highlightCurrentLine();
 }



 int MdEditor::lineNumberAreaWidth()
 {
     int digits = 1;
     int max = qMax(1, blockCount());
     while (max >= 10) {
         max /= 10;
         ++digits;
     }

     int space = 10 + fontMetrics().width(QLatin1Char('9')) * digits;

     return space;
 }

 int MdEditor::countWords() const
 {
     QString text = toPlainText();

     // empty or only whitespaces?
     if (text.trimmed().isEmpty()) {
         return 0;
     }

     int words = 0;
     bool lastWasWhitespace = false;
     bool firstCharacter = false;

     for (int i = 0; i < text.count(); ++i) {
         if (text.at(i).isSpace()) {
             if (firstCharacter && !lastWasWhitespace) {
                 words++;
             }
             lastWasWhitespace = true;
         }
         else
         {
             firstCharacter = true;
             lastWasWhitespace = false;
         }
     }

     if (!lastWasWhitespace && text.count() > 0) {
         words++;
     }

     return words;
 }



 void MdEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
 {
     setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
 }



 void MdEditor::updateLineNumberArea(const QRect &rect, int dy)
 {
     if (dy)
         lineNumberArea->scroll(0, dy);
     else
         lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

     if (rect.contains(viewport()->rect()))
         updateLineNumberAreaWidth(0);
 }

 void MdEditor::save()
 {
    WriteContentToFile *new_thread = new WriteContentToFile(QCoreApplication::applicationDirPath());
    new_thread->text = this->toPlainText();
    new_thread->start();

 }


 void MdEditor::resizeEvent(QResizeEvent *e)
 {
     QPlainTextEdit::resizeEvent(e);

     QRect cr = contentsRect();
     lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
 }




 void MdEditor::highlightCurrentLine()
 {
     QList<QTextEdit::ExtraSelection> extraSelections;

     if (!isReadOnly()) {
         QTextEdit::ExtraSelection selection;

         QColor lineColor = QColor(Qt::gray).lighter(160);

         selection.format.setBackground(lineColor);
         selection.format.setProperty(QTextFormat::FullWidthSelection, true);
         selection.cursor = textCursor();
         selection.cursor.clearSelection();
         extraSelections.append(selection);
     }

     setExtraSelections(extraSelections);
 }



 void MdEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
 {
     QPainter painter(lineNumberArea);
     QPalette palette = lineNumberArea->palette();
     palette.setCurrentColorGroup(QPalette::Active);

     painter.fillRect(event->rect(), palette.color(QPalette::Background));


     QTextBlock block = firstVisibleBlock();
     int blockNumber = block.blockNumber();
     int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
     int bottom = top + (int) blockBoundingRect(block).height();

     while (block.isValid() && top <= event->rect().bottom()) {
         if (block.isVisible() && bottom >= event->rect().top()) {
             QString number = QString::number(blockNumber + 1);
             painter.setPen(Qt::black);
             painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                              Qt::AlignRight+3, number);
         }

         block = block.next();
         top = bottom;
         bottom = top + (int) blockBoundingRect(block).height();
         ++blockNumber;
     }
 }
