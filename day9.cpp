#include <QDebug>
#include <QFile>

#include "day9.h"

//-------------------------------------------------------------------------------------------------
struct Corner
{
    int x;
    int y;

    Corner(int x, int y) : x(x), y(y) {}
};

//-------------------------------------------------------------------------------------------------
struct Area
{
    Corner c1;
    Corner c2;
    Corner c3;
    Corner c4;
    qint64 size;

    Area(Corner t1, Corner t2, qint64 s) : c1(t1), c2(t2), c3(Corner(t1.x, t2.y)), c4(Corner(t2.x, t1.y)), size(s) {}

    bool operator <(const Area &a) {
        return size > a.size;
    }
};

//-------------------------------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const Corner& t)
{
    dbg.nospace() << "Corner: " << t.x << " | " << t.y;
    return dbg;
}

//-------------------------------------------------------------------------------------------------
QDebug operator<<(QDebug dbg, const Area& a)
{
    dbg.nospace() << "Area-Size: " << a.size << ", \t" << a.c1  << " &\t " << a.c2 << ", \t" << a.c3  << " &\t " << a.c4;
    return dbg;
}

//-------------------------------------------------------------------------------------------------
Day9::Day9()
{
    testThings();
    return;

    QFile file("../../input/day9.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QList<Corner> corners;
    while (!file.atEnd()) {
        const QString line = file.readLine();
        const QStringList parts = line.simplified().split(",");
        corners.append(Corner(parts.first().toInt(), parts.last().toInt()));
    }

    file.close();

    QList<Area> areas;
    for (const Corner &t1 : corners) {
        for (const Corner &t2 : corners) {
            qint64 areaSize = area(t1, t2);
            areas.append(Area(t1, t2, areaSize));
        }
    }

    std::sort(areas.begin(), areas.end());

    for (const Area &a : areas) {
        qDebug() << "Tile-Size:" << a.size << a.c1 << " ------ " <<  a.c2;
    }
}

//-------------------------------------------------------------------------------------------------
qint64 Day9::area(const Corner &t1, const Corner &t2)
{
    return qint64(std::abs(t1.x - t2.x) + 1) * qint64(std::abs(t1.y - t2.y) + 1);
}

//-------------------------------------------------------------------------------------------------
void Day9::testThings()
{
    QList<Corner> tiles = {
        Corner(7,1),
        Corner(11,1),
        Corner(11,7),
        Corner(9,7),
        Corner(9,5),
        Corner(2,5),
        Corner(2,3),
        Corner(7,3)
    };

    QList<Area> areas;
    for (const Corner &t1 : tiles) {
        for (const Corner &t2 : tiles) {
            if (t1.x == t2.x && t1.y == t2.y)
                break;

            qint64 areaSize = area(t1, t2);
            areas.append(Area(t1, t2, areaSize));
        }
    }

    std::sort(areas.begin(), areas.end());

    for (const Area &a : areas) {
        qDebug() << a;
    }

















}













