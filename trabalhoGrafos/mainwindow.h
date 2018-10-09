#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>

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

private:
    Ui::MainWindow *ui;
    QPushButton *procurarBtn;
    QLineEdit *arquivoEdit;

};

#endif // MAINWINDOW_H
