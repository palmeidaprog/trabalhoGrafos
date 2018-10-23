#include "maincontroller.h"
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
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".GraphML");

    QStringList filename;
    if(dialog.exec()) {
        filename = dialog.selectedFiles();
    }

    GraphMLParser(filename[0].toStdString());





//    grafos::Grafo<std::string> grafo(fopen(filename[0].toLatin1().data(), "rt"));

//    QMessageBox msgBox;
//    msgBox.setWindowTitle("Grafo");
//    QString s = QString::fromStdString(grafo.getLista());
//    arquivoEdit->setText(filename[0].toLatin1().data());
//    if(!filename.empty()) {
//        msgBox.setText(s);
//        msgBox.addButton(QMessageBox::Ok);
//        //msgBox.defaultButton(QMessageBox::Ok);
//        if(msgBox.exec()) {
//            //
//        }
//    }

//    grafo.pegaGML("teste.gml");
//    msgBox.setWindowTitle("Salvo");
//    msgBox.setText("GML salvo");
//    msgBox.exec();
}

