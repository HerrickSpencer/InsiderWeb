#pragma once
#include <QDialog>

namespace Ui {
    class ChooseBuildTypeDialog;
}

class BuildTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuildTypeDialog(QWidget *parent, const int * piVersion, QString &URLtoDL);
    ~BuildTypeDialog();
    int GetURLChoice(QString &URLtoDL);

public slots:
    int exec();
private slots:
    void on_list_itemSelectionChanged();

private:
    Ui::ChooseBuildTypeDialog *ui;
    int m_piVer;
    QString* m_selectionReturn;
};

