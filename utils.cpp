#include "utils.h"
#include <QString>
#include <QFile>
#include <QRegExp>
#include <QDebug>

int Utils::GetPiVersion(const QString &propFilePath)
{
    int version = 0;

    // open devices proc file
    QFile propFile(propFilePath);
    if (!propFile.exists())
    {
        SendMessage("Device Property file missing " + propFilePath);
        return 0;
    }
    if (!propFile.open(QFile::ReadOnly | QFile::Text))
    {
        SendMessage("Could not open device property file " + propFilePath);
        return 0;
    }
    QString deviceDesc = propFile.readAll();
    propFile.close();

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
        SendMessage("Version not found from " + propFilePath);
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
