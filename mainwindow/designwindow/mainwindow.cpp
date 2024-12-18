#include "mainwindow.h"
#include "ui_mainwidow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 連接 actionSave 動作到 saveFile 槽函數
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file: ") + file.errorString());
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
}
