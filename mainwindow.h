#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void UrlChanged();
    void download(const QNetworkRequest &request);
    void unsupportedContent(QNetworkReply *reply);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool DownloadIso(QUrl url);
    bool isIsoUrl(QUrl url);
};

#endif // MAINWINDOW_H
