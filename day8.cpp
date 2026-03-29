#include <QDebug>
#include <QFile>

#include "day8.h"

//-----------------------------------------------
struct JunctionBox
{
    int x;
    int y;
    int z;
    bool inCircuit;

    JunctionBox(int x, int y, int z)
        : x(x), y(y), z(z), inCircuit(false) {}

    bool operator == (const JunctionBox &j) const {
        return j.x == x && j.y == y && j.z == z/* && j.inCircuit == inCircuit*/;
    }
};

//-----------------------------------------------
struct Connection
{
    JunctionBox box1;
    JunctionBox box2;
    float distance;

    Connection(const JunctionBox &b1, const JunctionBox &b2) : box1(b1), box2(b2), distance(sqrt(pow((b2.x - b1.x), 2) + pow((b2.y - b1.y), 2) + pow((b2.z - b1.z), 2))) {}

    bool isConnected(const JunctionBox &b1, const JunctionBox &b2) const {
        return (box1 == b1 && box2 == b2) || (box1 == b2 && box2 == b1);
    }

    bool operator <(const Connection &c) {
        return distance < c.distance;
    }
};

//-----------------------------------------------
QDebug operator<<(QDebug dbg, const JunctionBox& j)
{
    dbg.nospace() << "Box(" << j.x << ", " << j.y << ", " << j.z << ")";
    return dbg;
}

//-------------------------------------------------------------------------------------------------
inline size_t qHash(const JunctionBox& j, size_t seed = 0)
{
    return qHashMulti(seed, j.x, j.y, j.z, j.inCircuit);
}

//-------------------------------------------------------------------------------------------------
Day8::Day8()
{
    // 1100 -> too low
    QList<JunctionBox> inputCircuits;
    inputCircuits.append(JunctionBox(162,817,812));
    inputCircuits.append(JunctionBox(57,618,57));
    inputCircuits.append(JunctionBox(906,360,560));
    inputCircuits.append(JunctionBox(592,479,940));
    inputCircuits.append(JunctionBox(352,342,300));
    inputCircuits.append(JunctionBox(466,668,158));
    inputCircuits.append(JunctionBox(542,29,236));
    inputCircuits.append(JunctionBox(431,825,988));
    inputCircuits.append(JunctionBox(739,650,466));
    inputCircuits.append(JunctionBox(52,470,668));
    inputCircuits.append(JunctionBox(216,146,977));
    inputCircuits.append(JunctionBox(819,987,18));
    inputCircuits.append(JunctionBox(117,168,530));
    inputCircuits.append(JunctionBox(805,96,715));
    inputCircuits.append(JunctionBox(346,949,466));
    inputCircuits.append(JunctionBox(970,615,88));
    inputCircuits.append(JunctionBox(941,993,340));
    inputCircuits.append(JunctionBox(862,61,35));
    inputCircuits.append(JunctionBox(984,92,344));
    inputCircuits.append(JunctionBox(425,690,689));

    // QSet<JunctionBox> testCircuits = {
    //     { 162,817,812 },
    //     { 57,618,57 },
    //     { 906,360,560 },
    //     { 592,479,940 },
    //     { 352,342,300 },
    //     { 466,668,158 },
    //     { 542,29,236 },
    //     { 431,825,988 },
    //     { 739,650,466 },
    //     { 52,470,668 },
    //     { 216,146,977 },
    //     { 819,987,18 },
    //     { 117,168,530 },
    //     { 805,96,715 },
    //     { 346,949,466 },
    //     { 970,615,88 },
    //     { 941,993,340 },
    //     { 862,61,35 },
    //     { 984,92,344 },
    //     { 425,690,689 }
    // };

    // qDebug() << findClosest(JunctionBox(162,817,812), inputCircuits);
    // qDebug() << findClosest(JunctionBox(425,690,689), inputCircuits);

    QList<QList<JunctionBox>> resultCircuits;

    /*
    for (const JunctionBox &box : inputCircuits) {
         const JunctionBox &closestBox = findClosest(box, inputCircuits);
        qDebug() << "!" << box << closestBox;

        bool appended = false;
        for (QList<JunctionBox> &circuit : resultCircuits) {
            if (circuit.contains(closestBox)) {
                circuit.append(box);
                appended = true;
                break;
            }
        }

        if (!appended)
            resultCircuits.append(QList<JunctionBox>{ box });
    }
    */

    QList<Connection> connections;
    QList<JunctionBox> handlesBoxes;
    for (int i = 0; i < inputCircuits.size(); i++) {
        const JunctionBox &b1 = inputCircuits[i];
        handlesBoxes.append(b1);

        for (int j = 0; j < inputCircuits.size(); j++) {
            const JunctionBox &b2 = inputCircuits[j];

            if (b1 == b2 || i == j || handlesBoxes.contains(b2))
                continue;

            connections.append(Connection(b1, b2));
        }
    }

    int maxConnections  = 11;
    int connectionCount = 0;
    std::sort(connections.begin(), connections.end());
    for (const Connection &c : connections) {
        qDebug() << c.box1 << c.box2 << c.distance;

        if (maxConnections == connectionCount)
            break;

        connectionCount++;

        const JunctionBox &b1 = c.box1;
        const JunctionBox &b2 = c.box2;

        bool box1InList = false;
        bool box2InList = false;
        // Check if box1 or box2 are in the resultCircuits-list
        for (QList<JunctionBox> &circuit : resultCircuits) {
            if (circuit.contains(b1))
                box1InList = true;

            if (circuit.contains(b2))
                box2InList = true;
        }

        if (!box1InList && !box2InList /*&& connectionCount < maxConnections*/) {
            resultCircuits.append(QList<JunctionBox>({ b1, b2 }));
            // connectionCount++;
            continue;
        }

        // If both boxes are in the resultCircuits-list, then skip
        if (box1InList && box2InList)
            continue;

        // At this stage, at least one box is not in the resultCircuits-list
        for (QList<JunctionBox> &circuit : resultCircuits) {
            if (circuit.contains(b1) /*&& connectionCount < maxConnections*/) {
                circuit.append(b2);
                // connectionCount++;
                box2InList = true;
                break;
            }

            if (circuit.contains(b2) /*&& connectionCount < maxConnections*/) {
                circuit.append(b1);
                // connectionCount++;
                box1InList = true;
                break;
            }
        }

        if (!box1InList) {
            resultCircuits.append(QList<JunctionBox>({ b1 }));
            // connectionCount++;
            continue;
        }

        if (!box2InList) {
            resultCircuits.append(QList<JunctionBox>({ b2 }));
            // connectionCount++;
            continue;
        }
    }

    for (auto r : resultCircuits)
        qDebug() << r.size() << r;
    // qDebug() << resultCircuits;



    return;
    while (!inputCircuits.isEmpty()) {
        auto pair = findClosest(inputCircuits);

        if (pair.first < 0 || pair.second < 0)
            break;

        bool appended = false;
        for (QList<JunctionBox> &circuit : resultCircuits) {
            if (circuit.contains(inputCircuits.at(pair.second))) {
                circuit.append(inputCircuits.at(pair.first));
                appended = true;
                break;
            }
        }

        if (!appended)
            resultCircuits.append(QList<JunctionBox>{ inputCircuits.at(pair.first) });

        inputCircuits.removeAt(pair.first);
    }

    for (auto c : resultCircuits) {
        qDebug() << c;
    }


    return;
    QFile file("../../input/day8.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    file.close();

    // QList<Circuit> circuits;
    // for (const QString &line : input) {
    //     const QStringList parts = line.split(",");

    //     JunctionBox j(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());
    //     circuits.append(Circuit(j));
    // }

    // qDebug() << circuits;
}

//-------------------------------------------------------------------------------------------------
float Day8::calcDistance(const JunctionBox &j1, const JunctionBox &j2)
{
    return sqrt(pow((j2.x - j1.x), 2) + pow((j2.y - j1.y), 2) + pow((j2.z - j1.z), 2));
}

//-------------------------------------------------------------------------------------------------
const JunctionBox &Day8::findClosest(const JunctionBox &j, const QList<JunctionBox> boxes)
{
    int index = -1;
    float distance = -1;
    for (int i = 0; i < boxes.size(); i++) {
        if (j == boxes.at(i))
            continue;

        int calculatedDistance = calcDistance(j, boxes.at(i));

        if (distance == -1 || distance > calculatedDistance) {
            distance = calculatedDistance;
            index = i;
        }
    }

    return boxes.at(index);
}

//-------------------------------------------------------------------------------------------------
const QPair<int, int> Day8::findClosest(const QList<JunctionBox> boxes)
{
    float distance = -1;
    int indexBox1 = -1;
    int indexBox2 = -1;

    for (int i = 0; i < boxes.size(); i++) {
        for (int j = 0; j < boxes.size(); j++) {
            if (i == j)
                continue;

            int calculatedDistance = calcDistance(boxes.at(i), boxes.at(j));

            if (distance == -1 || distance > calculatedDistance) {
                distance = calculatedDistance;
                indexBox1 = i;
                indexBox2 = j;
            }
        }
    }

    return qMakePair(indexBox1, indexBox2);
}
