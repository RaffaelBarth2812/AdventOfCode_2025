#include <QRegularExpression>
#include <QDebug>
#include <QFile>

#include "day6_2.h"

Day6_2::Day6_2()
{
    // QStringList test = { "  95", " 986", "2948", "6129", "+   " };
    // qDebug() << calcResultFromLines(test);

    // return;

    QFile file("../../input/day6.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.replace("\n", ""));
    }

    QString signs = input.takeLast();
    int rowSize = input.count();

    const QRegularExpression e("[+*]");

    int lastIndex = 0;
    qint64 sum = 0;
    for (int i = 0; i < signs.count(e); i++) {
        QStringList numbers;
        int firstIndex  = signs.indexOf(e, lastIndex);
        int secondIndex = signs.indexOf(e, firstIndex + 1);
        lastIndex = secondIndex;

        for (int j = 0; j < rowSize; j++)
            numbers.append(input[j].mid(firstIndex, secondIndex - firstIndex - 1));

        numbers.append(signs.mid(firstIndex, secondIndex - firstIndex - 1));
        sum += calcResultFromLines(numbers);
    }

    qDebug() << "Sum:" << sum;
}

qint64 Day6_2::calcResultFromLines(const QStringList &input) const
{
    const int size = input.first().size();
    const bool isPlus = input.last().contains("+");

    qint64 calcSum = 0;
    for (int j = size - 1; j >= 0; j--) {
        QString n;
        for (int i = 0; i < input.count() - 1; i++)
            n.append(input[i][j]);

        int nValue = n.toInt();

        if (calcSum == 0) {
            calcSum = nValue;
            continue;
        }

        isPlus ? calcSum += nValue : calcSum *= nValue;
    }

    return calcSum;
}
