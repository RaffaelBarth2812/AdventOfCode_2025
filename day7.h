#ifndef DAY7_H
#define DAY7_H

#include <QStringList>

class Day7
{
public:
    Day7();

private:
    void executeTreeSplit(QStringList &tree);

    QList<int> indexesForChar(const QString &line, const QChar &sign);
};

#endif // DAY7_H
