#include <QDebug>
#include <QFile>

#include "day3_2.h"

static const int REMAINING_DIGITS = 12;

//-------------------------------------------------------------------------------------------------
Day3_2::Day3_2()
{
    QFile file("../../input/day3.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    qint64 sum = 0;
    for (const QString &line : input)
        sum += calcJoltage(line).toLongLong();

    qDebug() << "Sum:" << sum;
}

//-------------------------------------------------------------------------------------------------
QString Day3_2::calcJoltage(QString line)
{
    int toRemove = line.size() - REMAINING_DIGITS;
    QString result;

    for (QChar c : line) {
        while (!result.isEmpty() && toRemove > 0 && result.back() < c) {
            result.chop(1);
            --toRemove;
        }

        result.append(c);
    }

    return result.left(REMAINING_DIGITS);
}
