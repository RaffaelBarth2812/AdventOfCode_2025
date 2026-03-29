#include <QDebug>
#include <QFile>

#include "day4_2.h"

struct Coords
{
    int x;
    int y;

    Coords(int x, int y) : x(x), y(y) {}
};

static const QString EMPTY_FIELD = ".";

//-------------------------------------------------------------------------------------------------
Day4_2::Day4_2()
{
    QFile file("../../input/day4.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    int removeCount = 0;
    while (true) {
        // Lesen
        int sum = 0;
        QList<Coords> coordsToDelete;
        for (int y = 0; y < input.length(); y++) {
            for (int x = 0; x < input.at(y).length(); x++) {
                if (neighbourAmount(x, y, input) < 4) {

                    coordsToDelete.append(Coords(x, y));
                    sum++;
                }
            }
        }

        if (sum == 0)
            break;

        // Replacen
        for (const Coords &c : coordsToDelete) {
            QString line = input.at(c.y);
            line.replace(c.x, 1, EMPTY_FIELD);
            input.replace(c.y, line);

            removeCount++;
        }
    }

    qDebug() << removeCount;
}

//-------------------------------------------------------------------------------------------------
int Day4_2::neighbourAmount(int x, int y, const QStringList &field)
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
