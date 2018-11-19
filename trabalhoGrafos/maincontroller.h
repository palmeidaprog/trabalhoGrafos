#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <iostream>
#include "grafo.h"
#include "graphmlparser.h"
#include "geradorgraphml.h"
#include "Kmeans.h"
#include <fstream>

using grafos::GraphMLParser;
using grafos::Grafo;
using std::cout;
using std::ofstream;
using grafos::kmeans::Kmeans;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void procurarGrafo();
    void salva();
    void mostraLista();
    void kmeansIt();
    void gerarPesos();

private:
    Ui::MainWindow *ui;
    Grafo<float> *grafo;
    QPushButton *procurarBtn, *salvaBtn, *mostraListaBtn, *kmeansBtn,
    *pesosBtn;
    QLineEdit *arquivoEdit, *clusterEdit, *iterEdit;
    QHBoxLayout *checkboxLayout;
    QCheckBox *colorirCheckbox;
    QLabel *verticesLabel, *arestasLabel, *tipoLabel;

};

#endif // MAINWINDOW_H
