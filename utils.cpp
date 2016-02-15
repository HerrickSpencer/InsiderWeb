#include "utils.h"
#include <QString>
#include <QFile>
#include <QRegExp>
#include <QDebug>

static const QString DEVICE_PROP_FILE = "./TestFiles/PropFile.txt";

int Utils::GetPiVersion()
{
    int version = 0;

    // open devices proc file
    QFile res_file(DEVICE_PROP_FILE);
    if (!res_file.exists())
    {
        SendMessage("Internal resource path missing " + DEVICE_PROP_FILE);
        return 0;
    }
    if (!res_file.open(QFile::ReadOnly | QFile::Text))
    {
        SendMessage("Could not open resource " + DEVICE_PROP_FILE);
        return 0;
    }
    QString deviceDesc = res_file.readAll();
    res_file.close();

    // Extract Pi ver from text
    QRegExp regEx("Pi (\\d+)");
    if (regEx.indexIn(deviceDesc))
    {
        QStringList versionList = regEx.capturedTexts();

        if (versionList.count() > 1)
        {
            bool ok;
            QString versionStr = versionList.at(1);
            SendMessage("version = " + versionStr);
            version = versionStr.toInt(&ok);
            if (ok)
            {
                return version;
            }
        }
    }

    if (!version)
    {
        SendMessage("Version not found from " + DEVICE_PROP_FILE);
    }
    return version;
}

void Utils::SendMessage(const QString& msg)
{
    qDebug()<<msg;
}

QString Utils::GetRtmUrl()
{
    return "url for rtm";
}
