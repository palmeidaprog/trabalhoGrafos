#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include "grafo.h"
#include "graphmlparser.h"
#include "geradorgraphml.h"

using grafos::GraphMLParser;
using grafos::Grafo;

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

private:
    Ui::MainWindow *ui;
    Grafo<float> *grafo;
    QPushButton *procurarBtn, *salvaBtn;
    QLineEdit *arquivoEdit;
    QLabel *verticesLabel, *arestasLabel, *tipoLabel;

};

#endif // MAINWINDOW_H
