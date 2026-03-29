#ifndef DAY10_H
#define DAY10_H

#include <QBitArray>

class Day10
{
public:
    Day10();

    int       processLine(const QString &line);
    QBitArray buttonToBinary(const QList<int> numbers, const int size) const;
    int       calculateButtonPresses(QBitArray mask, QList<QBitArray> buttons) const;
};

#endif // DAY10_H
