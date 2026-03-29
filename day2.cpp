#include <QDebug>
#include <QFile>

#include "day2.h"

//-------------------------------------------------------------------------------------------------
Day2::Day2()
    : mInvalidIdCount(0)
{
    QFile file("../../input/day2.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    for (const QString &sequence : input.split(",")) {
        const QStringList numbers = sequence.split("-");

        qDebug() << "Starting with:" << sequence;

        invalidIdAmount(numbers.first().toLongLong(), numbers.last().toLongLong());
    }

    qDebug() << "Invalid IDs:" << mInvalidIdCount;
}

//-------------------------------------------------------------------------------------------------
void Day2::invalidIdAmount(qint64 first, qint64 last)
{
    QString n1 = QString::number(first);
    QString n2 = QString::number(last);
    int l1 = n1.length();
    int l2 = n2.length();


    for (qint64 i = n1.mid(0, l1 / 2).toInt(); i <= n2.mid(0, l2 / 2 + 1).toInt(); i++) {
        qint64 number = (QString::number(i) + QString::number(i)).toLongLong();

        if (number >= first && number <= last) {
            mInvalidIdCount += number;
            qDebug() << "Number found:" << number << "Current score:" << mInvalidIdCount;
        }
    }
}
