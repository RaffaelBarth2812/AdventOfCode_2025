#include <QDebug>
#include <QFile>

#include "day6.h"

//-------------------------------------------------------------------------------------------------
Day6::Day6()
{
    QFile file("../../input/day6.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    QString signs = input.takeLast();

    int rowSize = input.count();
    int colSize = input.first().split(" ").count();

    qint64 sum = 0;
    for (int j = 0; j < colSize; j++) {
        const QString sign = signs.split(" ").at(j);

        qint64 calcSum = 0;
        for (int i = 0; i < rowSize; i++) {
            qint64 n = input.at(i).split(" ").at(j).toInt();

            if (calcSum == 0) {
                calcSum = n;
                continue;
            }

            if (sign == "*") {
                calcSum *= n;
                continue;
            }

            calcSum += n;
        }

        sum += calcSum;
    }

    qDebug() << "Summe:" << sum;
}
