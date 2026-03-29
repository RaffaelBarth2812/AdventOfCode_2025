#ifndef DAY10_2_H
#define DAY10_2_H

#include <QBitArray>

class Day10_2
{
public:
    Day10_2();

    int       processLine(const QString &line);
    QBitArray buttonToBinary(const QList<int> numbers, const int size) const;
    int       calculateButtonPresses(QBitArray mask, QList<QBitArray> buttons, const QList<int> joltages) const;
};

#endif // DAY10_2_H
