#ifndef FILEEXPLORERWIDGET_H
#define FILEEXPLORERWIDGET_H

#include <QWidget>
#include <QDockWidget>

namespace Ui {
class FileExplorerWidget;
}
class QFileSystemModel;
class QSortFilterProxyModel;


class FileExplorerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileExplorerWidget(QWidget *parent = 0);
    ~FileExplorerWidget();

signals:
    void fileSelected(const QString &filePath);

private slots:
    void fileOpen(const QModelIndex &index);

private:
    Ui::FileExplorerWidget *ui;
    QFileSystemModel *model;
    QSortFilterProxyModel *sortModel;
};

#endif // FILEEXPLORERWIDGET_H
