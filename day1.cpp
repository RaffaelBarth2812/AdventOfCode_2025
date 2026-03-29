#include <QFile>
#include <QDir>

#include "day1.h"

//-------------------------------------------------------------------------------------------------
enum Direction {
    Left,
    Right
};

//-------------------------------------------------------------------------------------------------
struct Dial {

    static const int MAX = 100;
    static const int MIN = 0;

    int dial;
    int zeroCount;

    Dial(int d)
        : dial(d), zeroCount(0) { qDebug() << "The dial starts by pointing at" << d; }

    //---------------------------------------------------------------------------------------------
    void newRotation(Direction d, int amount) {
        for (int i = 0; i < amount; i++) {
            if (d == Left) {
                dial -= 1;
            } else
                dial += 1;

            if ((dial % 100) == 0)
                zeroCount++;
        }

        if (d == Left)
            qDebug() << "The dial is rotated L" << amount << " to point at" << dial << "\t-------->" << zeroCount;
        else
            qDebug() << "The dial is rotated R" << amount << " to point at" << dial << "\t-------->" << zeroCount;
    }

    //---------------------------------------------------------------------------------------------
    void outputCurrentDial() {
        qDebug() << "Current dial at:" << dial << "with a zero-count of:" << zeroCount;
    }
};

//-------------------------------------------------------------------------------------------------
Day1::Day1(QObject *parent)
    : QObject{parent}
{
    // 50 + 150 = 200 -> 0


    //d.newRotation(Right, 1000);

/*
    d.newRotation(Left, 68);
    d.newRotation(Left, 30);
    d.newRotation(Right, 48);
    d.newRotation(Left, 5);
    d.newRotation(Right, 60);
    d.newRotation(Left, 55);
    d.newRotation(Left, 1);
    d.newRotation(Left, 99);
    d.newRotation(Right, 14);
    d.newRotation(Left, 82);
*/

    QFile file("../../input/day1.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList lines;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        lines.append(line.simplified());
    }

    Dial d(50);

    for (const QString &rotation : lines) {
        int amount = rotation.mid(1).toInt();
        if (rotation.startsWith("R")) {
            d.newRotation(Right, amount);
        } else {
            d.newRotation(Left, amount);
        }
    }

    d.outputCurrentDial();
}
