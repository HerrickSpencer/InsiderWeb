#include <QApplication>
#include "utils.h"
#include <iostream>
#include <QWidget>
#include "buildtypedialog.h"
#include "insiderwebdialog.h"

QString DEVICE_PROP_FILE;
QString RTM_DL_URL;
QString INSIDER_URL;
QString ISO_DEST_PATH;

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);

    if (argc != 5)
    {
        Utils::SendMessage(QString("INCORRECT SYNTAX:\n%1 devPropFile urlOfRTMDL urlOfInsiderStartPage targetIsoPath").arg(argv[0]));
        return -1;
    }
    DEVICE_PROP_FILE = QString(argv[1]);
    RTM_DL_URL = argv[2];
    INSIDER_URL = argv[3];
    ISO_DEST_PATH = argv[4];

    // Determine device version/rev
    int piVer = Utils::GetPiVersion(DEVICE_PROP_FILE);
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
        urlToDl = RTM_DL_URL;
    }
    else
    {
        // if Insider Go directly to the insider web choice
        InsiderWebDialog* pInsiderWebDialog = new InsiderWebDialog(0, urlToDl, INSIDER_URL);
        int dialogResult = pInsiderWebDialog->exec();

        if (!dialogResult)
        {
            // User canceled choice
            Utils::SendMessage(QString("User canceled WinIot Choice"));
            return 1;
        }
    }

    // do download with urlToDl
    Utils::SendMessage(QString("Set download to %1").arg(urlToDl));


    return piVer;

    /*MainWindow w;
    w.show();

    return a.exec();
                    */
}
