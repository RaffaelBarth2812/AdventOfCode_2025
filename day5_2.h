#ifndef DAY5_2_H
#define DAY5_2_H

#include <QList>

class Range;

class Day5_2
{
public:
    Day5_2();

private:
    qint64 freshCountForRange(qint64 from, qint64 to);
    bool overlapping(const QPair<qint64, qint64> &p1, const QPair<qint64, qint64> &p2);
};

#endif // DAY5_2_H
