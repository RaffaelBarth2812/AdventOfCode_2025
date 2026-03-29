#include <QDebug>
#include <QFile>
#include <QSet>

#include "day5_2.h"

//-------------------------------------------------------------------------------------------------
Day5_2::Day5_2()
{
    QFile file("../../input/day5.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList rangesStrings;

    while (!file.atEnd()) {
        QString line = file.readLine();

        if (line == "\n")
            break;

        rangesStrings.append(line.simplified());
    }

    QSet<QPair<qint64, qint64>> set;
    for (int i = 0; i < rangesStrings.size(); i++) {
        const QStringList numbers = rangesStrings[i].split("-");

        qint64 first = numbers.first().toLongLong();
        qint64 to    = numbers.last().toLongLong();

        set.insert({ first, to });
    }

    bool changes = true;
    while (changes) {
        changes = false;

        for (auto r1 : set) {
            for (auto r2 : set) {
                if (r1 == r2)
                    continue;

                if (!overlapping(r1, r2))
                    continue;

                qint64 first  = std::min(r1.first, r2.first);
                qint64 second = std::max(r1.second, r2.second);
                set.remove(r1);
                set.remove(r2);
                set.insert({ first, second });

                changes = true;
            }
        }
    }

    qint64 freshCount = 0;
    for (auto r : set)
        freshCount += freshCountForRange(r.first, r.second);

    qDebug() << "Sum:" << freshCount;
}

//-------------------------------------------------------------------------------------------------
qint64 Day5_2::freshCountForRange(qint64 from, qint64 to)
{
    if (from == to)
        return 1;

    return to - from + 1;
}

//-------------------------------------------------------------------------------------------------
bool Day5_2::overlapping(const QPair<qint64, qint64> &p1, const QPair<qint64, qint64> &p2)
{
    bool fitIt   = (p1.first <= p2.first && p1.second >= p2.second) || (p2.first <= p1.first && p2.second >= p1.second);
    bool overlap = (p1.first <= p2.second && p2.first <= p1.second) || (p2.first <= p1.second && p1.first <= p2.second);
    return fitIt || overlap;

}
