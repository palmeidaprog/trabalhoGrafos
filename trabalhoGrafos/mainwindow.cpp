#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    procurarBtn = ui->pushButton;
    arquivoEdit = ui->arquivoEdit;
    connect(procurarBtn, SIGNAL (clicked()), this, SLOT (procurarGrafo()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::procurarGrafo() {
    arquivoEdit->setText("Procurado");
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    QStringList filenames;
    if(dialog.exec()) {
        filenames = dialog.selectedFiles();
    }

    QMessageBox msgBox;
    msgBox.setWindowTitle("Grafos Selecionados");
    QString s = "";
    for(auto i : filenames) {
        s += i + " ";
    }
    arquivoEdit->setText(s);
}


