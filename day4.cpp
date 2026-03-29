#include <QDebug>
#include <QFile>

#include "day4.h"

//-------------------------------------------------------------------------------------------------
Day4::Day4()
{
    QFile file("../../input/day4.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    int sum = 0;
    for (int y = 0; y < input.length(); y++) {
        for (int x = 0; x < input.at(y).length(); x++) {
            if (neighbourAmount(x, y, input) < 4)
                sum++;
        }
    }

    qDebug() << sum;
}

//-------------------------------------------------------------------------------------------------
int Day4::neighbourAmount(int x, int y, const QStringList &field)
{
    if (field.at(y).at(x) == ".")
        return 99;

    int count = 0;
    const int ySize = field.length();
    const int xSize = field.at(y).length();

    for (int yCoord = y - 1; yCoord <= y + 1; yCoord++) {
        for (int xCoord = x - 1; xCoord <= x + 1; xCoord++) {
            if (xCoord < 0 || yCoord < 0 || xCoord >= xSize || yCoord >= ySize)
                continue;

            if (x == xCoord && y == yCoord)
                continue;

            if (field.at(yCoord).at(xCoord) == "@")
                count++;
        }
    }

    return count;
}
