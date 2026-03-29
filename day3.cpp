#include <QDebug>
#include <QFile>

#include "day3.h"

//-------------------------------------------------------------------------------------------------
Day3::Day3()
{
    QFile file("../../input/day3.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    int sum = 0;
    for (const QString &line : input) {
        sum += sumJoltage(line);
    }

    qDebug() << sum;
}

//-------------------------------------------------------------------------------------------------
int Day3::sumJoltage(const QString &line)
{
    for (int i = 9; i >= 1; i--) {
        for (int j = 9; j >= 1; j--) {
            const QString left  = QString::number(i);
            const QString right = QString::number(j);

            const int leftIndex = line.indexOf(left);
            const int rightIndex = line.lastIndexOf(right);

            if (leftIndex == rightIndex)
                continue;

            if (leftIndex >= 0 && rightIndex >= 0 && leftIndex < rightIndex)
                return QString(left + right).toInt();
        }
    }

    return 0;
}
