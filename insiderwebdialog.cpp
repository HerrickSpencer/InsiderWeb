#include "insiderwebdialog.h"
#include "ui_insiderwebdialog.h"
#include <QRegExp>

InsiderWebDialog::InsiderWebDialog(QWidget *parent, QString &urlToDownload, const QString startPage) :
    QDialog(parent),
    ui(new Ui::InsiderWebDialog),
    m_urlToDownload(&urlToDownload)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);

    connect(ui->webView->page(),SIGNAL(downloadRequested(QNetworkRequest)),this,SLOT(DownloadRequested(QNetworkRequest)));
    connect(ui->webView->page(),SIGNAL(unsupportedContent(QNetworkReply*)),this,SLOT(UnsupportedContentRequested(QNetworkReply*)));

    ui->webView->load(QUrl(startPage));
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

