#include "maincontroller.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    procurarBtn = ui->pushButton;
    arquivoEdit = ui->arquivoEdit;
    arquivoEdit->setReadOnly(true);
    verticesLabel = ui->verticesLabel;
    arestasLabel = ui->arestasLabel;
    tipoLabel = ui->tipoLabel;
    salvaBtn = ui->salvaBtn;
    kmeansBtn = ui->kmeansBtn;
    mostraListaBtn = ui->mostraListaBtn;
    colorirCheckbox = ui->colorirCheckbox;
    checkboxLayout = ui->checkBoxLayout;
    iterEdit = ui->iterEdit;
    clusterEdit = ui->clusterEdit;
    pesosBtn = ui->pesosBtn;
    distanciaCheckbox = ui->distanciaCheckbox;
    salvaClustersBtn = ui->salvaClustersBtn;
    checkboxLayout->setAlignment(Qt::AlignHCenter);
    connect(salvaClustersBtn, SIGNAL (clicked()), this,
            SLOT (salvaClusters()));
    connect(kmeansBtn, SIGNAL (clicked()), this, SLOT (kmeansIt()));
    connect(salvaBtn, SIGNAL (clicked()), this, SLOT (salva()));
    connect(procurarBtn, SIGNAL (clicked()), this, SLOT (procurarGrafo()));
    connect(mostraListaBtn, SIGNAL (clicked()), this, SLOT (mostraLista()));
    connect(pesosBtn, SIGNAL (clicked()), this, SLOT (gerarPesos()));
    srand(time(NULL));
}

MainWindow::~MainWindow() {
    delete ui;
    delete grafo;
    delete kmeans;
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
        pesosBtn->setEnabled(true);
        salvaClustersBtn->setEnabled(true);
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
    kmeans = new Kmeans<float>(clusterEdit->text().toInt(), grafo,
                         iterEdit->text().toInt(),
                         colorirCheckbox->isChecked(),
                         (distanciaCheckbox->isChecked() ?
                              KmeansModo::DISTANCIA_EUCLIDIANA :
                              KmeansModo::PESO_ARESTAS));
    QMessageBox msg;
    msg.setWindowTitle("Sucesso!");
    msg.setText("K-means executado com sucesso");
    msg.exec();

}

void MainWindow::gerarPesos() {
    grafo->gerarPesosAleatorios(1);

    QMessageBox m;
    m.setWindowTitle("Sucesso!");
    m.setText("Pesos aleatorios gerados entre 0 e 1");
    m.exec();
}

void MainWindow::salvaClusters() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDefaultSuffix(".txt");
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Salvar Clusters em Arquivo Texto"), "clusters.txt",
        tr("Arquivo texto (*.TXT)"));
    if(filename != "") {
        ofstream x(filename.toStdString());
        std::string y = kmeans->toString();
        x << y << std::endl;
        x.close();
    }
}
