#include "buildtypedialog.h"
#include "ui_buildtypedialog.h"
#include <QListWidgetItem>
#include "utils.h"

BuildTypeDialog::BuildTypeDialog(QWidget *parent, const int * piVersion, QString &buildSelection) :
    QDialog(parent),
    ui(new Ui::ChooseBuildTypeDialog),
    m_piVer(*piVersion),
    m_selectionReturn(&buildSelection)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() ^ Qt::WindowContextHelpButtonHint);
}

int BuildTypeDialog::exec()
{
    if (m_piVer > 2)
    {
        *m_selectionReturn = "Insider";
        return 0; // choice for RTM is only Pi ver 2
    }

    // Can choose Insider or RTM

    QString friendlyname = "Windows IoT RTM [RECOMMENDED]";
    QIcon icon = QIcon(QString(":/root/images/Windows_IoT.png"));
    QListWidgetItem *item = new QListWidgetItem(icon, friendlyname);
    item->setData(Qt::UserRole, QVariant("RTM"));
    ui->list->addItem(item);
    item->setSelected(true);

    friendlyname = "Windows IoT Insider Builds";
    QIcon iconInsider = QIcon(QString(":/root/images/Windows_IoT_Insider.png"));
    QListWidgetItem *itemInsider = new QListWidgetItem(iconInsider, friendlyname);
    itemInsider->setData(Qt::UserRole, QVariant("Insider"));
    ui->list->addItem(itemInsider);

    const QSize iconSize = QSize(32,32);
    ui->list->setIconSize(iconSize);

    return QDialog::exec();
}

BuildTypeDialog::~BuildTypeDialog()
{
    delete ui;
}

void BuildTypeDialog::on_list_itemSelectionChanged()
{
    QVariant itemSelected = ui->list->selectedItems().first()->data(Qt::UserRole);
    QString returnStr = itemSelected.toString();
    *m_selectionReturn = returnStr;
    Utils::SendMessage(QString("Selected item %1").arg(itemSelected.toString()));
}
