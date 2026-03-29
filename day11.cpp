#include <QDebug>
#include <QFile>

#include "day11.h"
//-----------------------------------------------
enum DeviceType {
    Start,
    Default,
    End
};

//-----------------------------------------------
struct Device
{
    DeviceType type;
    QString name;
    QList<Device*> devicesIn;
    QList<Device*> devicesOut;

    Device(const QString &n) : name(n)
    {
        if (n == "you") {
            type = Start;
            return;
        }

        if (n == "out") {
            type = End;
            return;
        }

        type = Default;
    }

    void addDeviceOut(Device *d) {
        devicesOut.append(d);
    }

    void addDeviceIn(Device *d) {
        devicesIn.append(d);
    }
};

//-------------------------------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const Device& d)
{
    dbg.nospace() << "Device: " << d.name << " | " << d.devicesOut;
    return dbg;
}

//-------------------------------------------------------------------------------------------------
Day11::Day11()
{
    QFile file("../../input/day11.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    file.close();

    // Testing ------
    input.clear();
    input ={ "aaa: you hhh",
             "you: bbb ccc",
             "bbb: ddd eee",
             "ccc: ddd eee fff",
             "ddd: ggg",
             "eee: out",
             "fff: out",
             "ggg: out",
             "hhh: ccc fff iii",
             "iii: out" };
    // --------------

    QList<Device> devices = { Device("out") };

    QMap<QString, QStringList> routes;
    for (const QString &line : input) {
        QStringList parts = line.split(":");
        QStringList last = parts.last().split(" ");
        last.removeAll("");

        routes[parts.first()] = last;
        devices.append(Device(parts.first()));
    }

    for (auto[key, value] : routes.asKeyValueRange()) {
        QString keyName       = key;
        QStringList keyValues = value;

        // Outgoing devices
        for (Device &device : devices) {
            if (device.name != keyName)
                continue;

            for (Device &subDevice : devices) {
                if (!keyValues.contains(subDevice.name))
                    continue;

                device.addDeviceOut(&subDevice);
            }
        }

        // Beispiel für Device e -> ingoing device: b, c
        // Ingoing devices
        for (auto[key, value] : routes.asKeyValueRange()) {
            QString subKeyName       = key;
            QStringList subKeyValues = value;

            if (!subKeyValues.contains(keyName))
                continue;

            qDebug() << keyName << subKeyValues;
        }
    }
}
