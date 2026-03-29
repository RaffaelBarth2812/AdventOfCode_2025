#include <QDebug>
#include <QFile>

#include "day5.h"

struct Range
{
    qint64 from;
    qint64 to;

    Range(qint64 f, qint64 t) : from(f), to(t) {}

    bool isInRange(qint64 n) {
        return n >= from && n <= to;
    }
};

//-------------------------------------------------------------------------------------------------
Day5::Day5()
{
    QFile file("../../input/day5.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList rangesStrings;
    QStringList ingredientIds;

    bool ingredientsReached = false;

    while (!file.atEnd()) {
        QString line = file.readLine();

        if (line == "\n") {
            ingredientsReached = true;
            continue;
        }

        if (ingredientsReached)
            ingredientIds.append(line.simplified());
        else
            rangesStrings.append(line.simplified());
    }

    // Ranges
    QList<Range> ranges;
    for (const QString &range : rangesStrings) {
        const QStringList &numbers = range.split("-");
        ranges.append(Range(numbers.first().toLongLong(), numbers.last().toLongLong()));
    }

    int freshCount = 0;
    bool found = false;

    // Ingredient IDs
    for (const QString &id : ingredientIds) {
        if (found) {
            found = false;
        }

        const qint64 n = id.toLongLong();

        for (Range r : ranges) {
            if (found)
                continue;

            if (r.isInRange(n)) {
                freshCount++;
                found = true;
            }
        }
    }

    qDebug() << freshCount;
}
