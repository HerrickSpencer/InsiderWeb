#include "insiderwebdialog.h"
#include "ui_insiderwebdialog.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegExp>
#include <QDebug>

InsiderWebDialog::InsiderWebDialog(QWidget *parent, QString &urlToDownload, const QString startPage) :
    QDialog(parent),
    ui(new Ui::InsiderWebDialog),
    m_urlToDownload(&urlToDownload)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);

    connect(ui->webView->page(),SIGNAL(downloadRequested(QNetworkRequest)),this,SLOT(DownloadRequested(QNetworkRequest)));
    connect(ui->webView->page(),SIGNAL(unsupportedContent(QNetworkReply*)),this,SLOT(UnsupportedContentRequested(QNetworkReply*)));

    connect(ui->webView->page()->networkAccessManager(),
            SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
            this,
            SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> & )));

    ui->webView->load(QUrl(startPage));
    qDebug()<< "loading:" << startPage;
}

InsiderWebDialog::~InsiderWebDialog()
{
    delete ui;
}

void InsiderWebDialog::DownloadRequested(const QNetworkRequest &request){
    qDebug()<<"Download Requested: "<<request.url();
    if (isIsoUrl(request.url()))
    {
        /*
        if(DownloadIso(request.url()))
        {
            qDebug()<<"Successfull Download";
        }
        else
        {
            qDebug()<<"Download Failed";
        }
        */
    }
}

void InsiderWebDialog::UnsupportedContentRequested(QNetworkReply * reply){
    qDebug()<<"Unsupported Content: "<<reply->url();
    if (isIsoUrl(reply->url()))
    {
        //*m_urlToDownload = (FIX reply->url using same method as mainwindow->download()
        /*        if (DownloadIso(reply->url()))
        {
            qDebug()<<"Successfull Download";
        }
        else
        {
            qDebug()<<"Download Failed";
        }
        */
    }
}

bool InsiderWebDialog::isIsoUrl(QUrl url)
{
    QString urlStr = url.toString();
    if (urlStr.contains(".iso", Qt::CaseInsensitive))
    {
        return true;
    }
    return false;
}

void InsiderWebDialog::sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist)
{

    qDebug() << "---frmBuyIt::sslErrorHandler: ";
    auto err = errlist.begin();

    while (err != errlist.end())
    {       
//        qDebug() << "ssl error: " << err;
    }
    // show list of all ssl errors
    //foreach (QSslError err, errlist)
    //qDebug() << "ssl error: " << err;

    qnr->ignoreSslErrors();
}
