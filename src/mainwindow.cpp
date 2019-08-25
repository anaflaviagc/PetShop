#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"cadastro.h"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cadastrarButton_clicked()
{
    Cadastro form2;
    form2.exec();

}
