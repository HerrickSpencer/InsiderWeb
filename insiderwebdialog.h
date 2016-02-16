#pragma once
#include <QDialog>

namespace Ui {
    class InsiderWebDialog;
}

class QSslError;
class QNetworkRequest;
class QNetworkReply;
class QRegExp;
class QDebug;
class QDialog;
class QUrl;

class InsiderWebDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsiderWebDialog(QWidget *parent, QString &urlToDownload, QString startPage);
    ~InsiderWebDialog();

public slots:
    void UnsupportedContentRequested(QNetworkReply *reply);
    void DownloadRequested(const QNetworkRequest &request);
    void sslErrorHandler(QNetworkReply* qnr, const QList<QSslError> & errlist);
private:
    Ui::InsiderWebDialog *ui;
    QString* m_urlToDownload;
    bool isIsoUrl(QUrl url);
};

