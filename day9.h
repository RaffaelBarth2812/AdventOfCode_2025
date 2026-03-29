#ifndef DAY9_H
#define DAY9_H

class Corner;

class Day9
{
public:
    Day9();

private:
    qint64 area(const Corner &t1, const Corner &t2);

    void testThings();
};

#endif // DAY9_H
