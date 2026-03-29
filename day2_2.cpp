#include <QDebug>
#include <QFile>

#include "day2_2.h"

//-------------------------------------------------------------------------------------------------
Day2_2::Day2_2()
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
void Day2_2::invalidIdAmount(qint64 first, qint64 last)
{
    QString n1 = QString::number(first);
    QString n2 = QString::number(last);
    int l1 = n1.length();
    int l2 = n2.length();

    int pos = 0;

    QList<qint64> numbersAdded;

    while(true) {
        if (pos == l2 / 2)
            break;

        pos++;

        for (int i = 1; i <= QString::number(9).repeated(l2 / 2).toLongLong(); i++) {
            int repeat = l2 / int(log10(i) + 1);
            qint64 id = QString::number(i).repeated(repeat).toLongLong();

            if (!numbersAdded.contains(id))
                checkInRange(id, first, last, &numbersAdded);
        }
    }

    if (l1 != l2) {
        pos = 0;

        while(true) {
            if (pos == l2 / 2)
                break;

            pos++;

            for (int i = 1; i <= QString::number(9).repeated(l1 / 2).toLongLong(); i++) {
                int repeat = l1 / int(log10(i) + 1);
                qint64 id = QString::number(i).repeated(repeat).toLongLong();

                if (!numbersAdded.contains(id))
                    checkInRange(id, first, last, &numbersAdded);
            }
        }
    }

    qDebug() << numbersAdded;
}

//-------------------------------------------------------------------------------------------------
void Day2_2::checkInRange(qint64 n, qint64 first, qint64 last, QList<qint64> *numbers)
{
    if (n >= first && n <= last) {
        mInvalidIdCount += n;
        qDebug() << "new add:" << n << "-->" << mInvalidIdCount;
        numbers->append(n);
    }
}
