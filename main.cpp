#include "mainwindow.h"
#include <QApplication>
#include "utils.h"
#include <iostream>
#include <QWidget>
#include "buildtypedialog.h"
#include "insiderwebdialog.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);

    // Determine device version/rev
    int piVer = Utils::GetPiVersion();
    Utils::SendMessage("Pi Version:" + piVer);

    if (!(piVer && (2|3)))
    {
        Utils::SendMessage(QString("Pi version is not supported %1").arg(piVer));
        return -1;
    }

    // show RTM/Insider picker, get choice of RTM or Insider
    QString buildChoice;
    int const *cPiVer = &piVer;
    BuildTypeDialog* pIoTOSPicker = new BuildTypeDialog(0, cPiVer, buildChoice);
    int dialogResult = pIoTOSPicker->exec();

    if (!dialogResult)
    {
        // User canceled choice
        Utils::SendMessage(QString("User canceled WinIot Choice"));
        return 1;
    }
    Utils::SendMessage(QString("OS Choice: %1 \n with result: %2").arg(buildChoice).arg(dialogResult));

    // Get url for download of OS Iso
    QString urlToDl;
    if (buildChoice == "RTM")
    {
        urlToDl = Utils::GetRtmUrl();
    }
    else
    {
        // if Insider Go directly to the insider web choice
        InsiderWebDialog* pInsiderWebDialog = new InsiderWebDialog(0, urlToDl, "http://auth.windowsondevices.com");
        int dialogResult = pInsiderWebDialog->exec();

        if (!dialogResult)
        {
            // User canceled choice
            Utils::SendMessage(QString("User canceled WinIot Choice"));
            return 1;
        }
    }

    // do download with urlToDl



     return piVer;

    /*MainWindow w;
    w.show();

    return a.exec();
                    */
}
