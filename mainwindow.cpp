#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->webView->load(QUrl("https://auth.windowsondevices.com"));
    ui->webView->load(QUrl("https://insider.windows.com"));
    connect( ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(UrlChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UrlChanged()
{
    QMessageBox::critical(this,"URL Change", tr("url changed to %1").arg(ui->webView->url().toString()));
}
