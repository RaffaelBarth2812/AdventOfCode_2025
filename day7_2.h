#ifndef DAY7_2_H
#define DAY7_2_H

#include <QStringList>

class Day7_2
{
public:
    Day7_2();

private:
    void executeTreeSplit(QStringList &tree);
    void countPossibilities(const QStringList &tree);

    QList<int> indexesForChar(const QString &line, const QChar &sign);
};

#endif // DAY7_2_H
