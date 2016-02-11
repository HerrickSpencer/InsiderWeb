#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView->page()->setForwardUnsupportedContent(true);
    connect(ui->webView->page(),SIGNAL(downloadRequested(QNetworkRequest)),this,SLOT(download(QNetworkRequest)));
    connect(ui->webView->page(),SIGNAL(unsupportedContent(QNetworkReply*)),this,SLOT(unsupportedContent(QNetworkReply*)));

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

void MainWindow::download(const QNetworkRequest &request){
    qDebug()<<"Download Requested: "<<request.url();
    if (isIsoUrl(request.url()))
    {
        if(DownloadIso(request.url()))
        {
            qDebug()<<"Successfull Download";
        }
        else
        {
            qDebug()<<"Download Failed";
        }
    }
}

void MainWindow::unsupportedContent(QNetworkReply * reply){
    qDebug()<<"Unsupported Content: "<<reply->url();
    if (isIsoUrl(reply->url()))
    {
        if (DownloadIso(reply->url()))
        {
            qDebug()<<"Successfull Download";
        }
        else
        {
            qDebug()<<"Download Failed";
        }
    }
}

bool MainWindow::isIsoUrl(QUrl url)
{
    QString urlStr = url.toString();
    if (urlStr.contains(".iso", Qt::CaseInsensitive))
    {
        return true;
    }
    return false;
}

bool MainWindow::DownloadIso(QUrl url){
    bool result = false;
    QString isoUrl = url.toString();
    isoUrl.remove(QRegExp("QUrl(\""));
    isoUrl.remove(QRegExp("\")"));
    qDebug()<<"To download: "<<isoUrl;

    QProcess wgetProcess;
    QString cmd = "wget -O /temp/Wow.iso " + isoUrl;
    qDebug()<<"Running: "<<cmd;
    wgetProcess.start(cmd);
    wgetProcess.waitForFinished();
    result = wgetProcess.exitStatus() == QProcess::NormalExit && wgetProcess.exitCode() == 0;
    QString resultStr = QString::number(result);
    qDebug()<<"Result: "<<resultStr;
    qDebug()<<"ErrorStr: "<<wgetProcess.errorString();
    wgetProcess.close();

    return result;
}

void MainWindow::on_pushButton_clicked()
{
    ui->webView->load(QUrl("http://localhost/Iso/14262.1000.160206-1700.RS1_RELEASE_IOTCoreRPi_armFRE.ISO"));
}
