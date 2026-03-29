#ifndef DAY8_H
#define DAY8_H

class JunctionBox;

class Day8
{
public:
    Day8();

private:
    float calcDistance(const JunctionBox &j1, const JunctionBox &j2);

    const JunctionBox &findClosest(const JunctionBox &j, const QList<JunctionBox> boxes);
    const QPair<int, int> findClosest(const QList<JunctionBox> boxes);
};

#endif // DAY8_H
