#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->webView->load(QUrl("https://auth.windowsondevices.com"));
    ui->webView->load(QUrl("https://insider.windows.com"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
