#ifndef DAY2_2_H
#define DAY2_2_H

#include <qtypes.h>
#include <QList>

class Day2_2
{
public:
    Day2_2();

private:
    void invalidIdAmount(qint64 first, qint64 last);
    void checkInRange(qint64 n, qint64 first, qint64 last, QList<qint64> *numbers);

    qint64 mInvalidIdCount;
};

#endif // DAY2_2_H
