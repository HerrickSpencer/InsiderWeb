#include "insiderwebdialog.h"
#include "ui_insiderwebdialog.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QRegExp>
#include <QDebug>
#include <QMessageBox>

InsiderWebDialog::InsiderWebDialog(QWidget *parent, QString &urlToDownload, const QString startPage) :
    QDialog(parent),
    ui(new Ui::InsiderWebDialog),
    m_urlToDownload(&urlToDownload)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);

    ui->webView->page()->setForwardUnsupportedContent(true);
    connect(ui->webView->page(),SIGNAL(downloadRequested(QNetworkRequest)),this,SLOT(DownloadRequested(QNetworkRequest)));
    connect(ui->webView->page(),SIGNAL(unsupportedContent(QNetworkReply*)),this,SLOT(UnsupportedContentRequested(QNetworkReply*)));

    connect(ui->webView->page()->networkAccessManager(),
            SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError> & )),
            this,
            SLOT(sslErrorHandler(QNetworkReply*, const QList<QSslError> & )));

    ui->webView->load(QUrl(startPage));
    qDebug()<< "loading:" << startPage;
#ifdef QT_DEBUG
   // connect( ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(UrlChanged()));
#endif
}

InsiderWebDialog::~InsiderWebDialog()
{
    delete ui;
}

void InsiderWebDialog::DownloadRequested(const QNetworkRequest &request){
    qDebug()<<"Download Requested: "<<request.url();
    if (isIsoUrl(request.url()))
    {
        SetDownloadIso(request.url());
    }
}

void InsiderWebDialog::UnsupportedContentRequested(QNetworkReply * reply){
    qDebug()<<"Unsupported Content: "<<reply->url();
    if (isIsoUrl(reply->url()))
    {
        SetDownloadIso(reply->url());
    }
}

bool InsiderWebDialog::isIsoUrl(const QUrl &url)
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
/*
    // show list of all ssl errors
    foreach (QSslError err, errlist)
    qDebug() << "ssl error: " << err;
*/
    qnr->ignoreSslErrors();
}

void InsiderWebDialog::SetDownloadIso(const QUrl &url){
    QString isoUrl = url.toString();
    isoUrl.remove(QRegExp("QUrl(\""));
    isoUrl.remove(QRegExp("\")"));
    qDebug()<<"To download: "<<isoUrl;
    *m_urlToDownload = isoUrl;
    this->accept(); //close window with 'ok'
}

void InsiderWebDialog::UrlChanged()
{
    QMessageBox::critical(this,"URL Change", tr("url changed to %1").arg(ui->webView->url().toString()));
}
