#pragma once
#include <QWidget>

class Utils
{
public:
    static int GetPiVersion(const QString &propFilePath);
    static void SendMessage(const QString &msg);
    static QString GetRtmUrl();
private:
    explicit Utils(const Utils& rhs) = delete;
    Utils& operator= (const Utils& rhs) = delete;
};


