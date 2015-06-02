#include "exportpdfdialog.h"
#include "ui_exportpdfdialog.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QPrinter>


ExportPdfDialog::ExportPdfDialog(const QString &fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportPdfDialog)
{
    ui->setupUi(this);


    if (!fileName.isEmpty())
    {
        QFileInfo info(fileName);
        QString exportFileName = info.absoluteFilePath().replace(info.suffix(), "pdf");
        ui->exportToLineEdit->setText(exportFileName);
    }


    ui->paperSizeComboBox->addItem(tr("A4 (210 x 297 мм, 8.26 x 11.69 дюймов)"), QPrinter::A4);
    ui->paperSizeComboBox->addItem(tr("Letter (8.5 x 11 дюймов, 215.9 x 279.4 мм)"), QPrinter::Letter);
    ui->paperSizeComboBox->addItem(tr("Legal (8.5 x 14 дюймов, 215.9 x 355.6 мм)"), QPrinter::Legal);
    ui->paperSizeComboBox->addItem(tr("A3 (297 x 420 мм)"), QPrinter::A3);
    ui->paperSizeComboBox->addItem(tr("A5 (148 x 210 мм)"), QPrinter::A5);
    ui->paperSizeComboBox->addItem(tr("A6 (105 x 148 мм)"), QPrinter::A6);
    ui->paperSizeComboBox->addItem(tr("B4 (250 x 353 мм)"), QPrinter::B4);
    ui->paperSizeComboBox->addItem(tr("B5 (176 x 250 мм, 6.93 x 9.84 дюймов)"), QPrinter::B5);

    // initialize Ok button state
    exportToTextChanged(fileName);
}

ExportPdfDialog::~ExportPdfDialog()
{
    delete ui;
}

QPrinter *ExportPdfDialog::printer()
{
    QString fileName = ui->exportToLineEdit->text();

    QPrinter::Orientation orientation;
    if (ui->portraitRadioButton->isChecked()) {
        orientation = QPrinter::Portrait;
    } else {
        orientation = QPrinter::Landscape;
    }

    QVariant v = ui->paperSizeComboBox->itemData(ui->paperSizeComboBox->currentIndex());
    QPrinter::PaperSize size = (QPrinter::PaperSize)v.toInt();

    QPrinter *p = new QPrinter();
    p->setOutputFileName(fileName);
    p->setOutputFormat(QPrinter::PdfFormat);
    p->setOrientation(orientation);
    p->setPaperSize(size);

    return p;
}

void ExportPdfDialog::exportToTextChanged(const QString &text)
{
    // only enable ok button if a filename was provided
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(!text.isEmpty());
}

void ExportPdfDialog::chooseFileButtonClicked()
{
    QString fileName = ui->exportToLineEdit->text();

    fileName = QFileDialog::getSaveFileName(this, tr("Export to PDF..."), fileName,
                                                  tr("PDF Files (*.pdf);;All Files (*)"));
    if (!fileName.isEmpty()) {
        ui->exportToLineEdit->setText(fileName);
    }
}
