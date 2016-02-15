#ifndef INSIDERWEBDIALOG_H
#define INSIDERWEBDIALOG_H

#include <QDialog>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
    class InsiderWebDialog;
}

class InsiderWebDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsiderWebDialog(QWidget *parent, QString &urlToDownload, const QString startPage);
    ~InsiderWebDialog();

public slots:
    void UnsupportedContentRequested(QNetworkReply *reply);
    void DownloadRequested(const QNetworkRequest &request);
private:
    Ui::InsiderWebDialog *ui;
    QString* m_urlToDownload;
    bool isIsoUrl(QUrl url);
};

#endif // INSIDERWEBDIALOG_H
