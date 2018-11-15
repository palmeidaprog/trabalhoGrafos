#include "maincontroller.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    procurarBtn = ui->pushButton;
    arquivoEdit = ui->arquivoEdit;
    verticesLabel = ui->verticesLabel;
    arestasLabel = ui->arestasLabel;
    tipoLabel = ui->tipoLabel;
    salvaBtn = ui->salvaBtn;
    connect(salvaBtn, SIGNAL (clicked()), this, SLOT (salva()));
    connect(procurarBtn, SIGNAL (clicked()), this, SLOT (procurarGrafo()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::procurarGrafo() {
    arquivoEdit->setText("Procurado...");
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".GraphML");

    QStringList filename;
    if(dialog.exec()) {
        filename = dialog.selectedFiles();
    }

    dialog.close();

    arquivoEdit->setText(filename[0]);
    GraphMLParser parser(arquivoEdit->text().toStdString());
    grafo = parser.getGrafo();
    tipoLabel->setText("Tipo: Orientado Valorado");
    QString q = "Vertices: " + QString::number(grafo->getVerticesNum());
    verticesLabel->setText(q);
    q = "Arestas: " + QString::number(grafo->getArestasNum());
    arestasLabel->setText(q);




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

void MainWindow::salva() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".GraphML");

    QStringList filename;
    if(dialog.exec()) {
        filename = dialog.selectedFiles();
    }

    dialog.close();
    grafos::GeradorGraphML gerador(filename[0].toStdString(), grafo);

}

