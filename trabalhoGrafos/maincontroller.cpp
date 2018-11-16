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
    kmeansBtn = ui->kmeansBtn;
    mostraListaBtn = ui->mostraListaBtn;
    connect(kmeansBtn, SIGNAL (clicked()), this, SLOT (kmeansIt()));
    connect(salvaBtn, SIGNAL (clicked()), this, SLOT (salva()));
    connect(procurarBtn, SIGNAL (clicked()), this, SLOT (procurarGrafo()));
    connect(mostraListaBtn, SIGNAL (clicked()), this, SLOT (mostraLista()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::procurarGrafo() {
    arquivoEdit->setText("Procurando...");
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".GraphML");
    QStringList filename;
    if(dialog.exec()) {
        filename = dialog.selectedFiles();
    }

    if(filename.size() > 0 && filename[0] != "") {
        arquivoEdit->setText(filename[0]);
        kmeansBtn->setEnabled(true);
        mostraListaBtn->setEnabled(true);
        salvaBtn->setEnabled(true);
        GraphMLParser parser(arquivoEdit->text().toStdString());
        grafo = parser.getGrafo();
        tipoLabel->setText("Tipo: Orientado Valorado");
        QString q = "Vertices: " + QString::number(grafo->getVerticesNum());
        verticesLabel->setText(q);
        q = "Arestas: " + QString::number(grafo->getArestasNum());
        arestasLabel->setText(q);
    }
}

void MainWindow::salva() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".GraphML");
    QString filename = QFileDialog::getSaveFileName(this, tr("Salvar Arquivo"),
        "grafo.GraphML", tr("Arquivo GraphML (*.GraphML)"));
    if(filename != "") {
        grafos::GeradorGraphML gerador(filename.toStdString(), grafo);
    }
}

void MainWindow::mostraLista() {
    QMessageBox m;
    m.setWindowTitle("Grafo - Lista Adjacente - Vertices: " +
                     QString::number(grafo->getVerticesNum()));
    m.setText(QString::fromStdString(grafo->getLista()));
    m.exec();
    ofstream x("grafo.txt");
    std::string y = grafo->getLista();
    x << y << std::endl;
    x.close();
}

void MainWindow::kmeansIt() {

}
