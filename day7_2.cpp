#include <QDebug>
#include <QFile>

#include "day7_2.h"

static const QChar BEAM_SIGN     = '|';
static const QChar START_SIGN    = 'S';
static const QChar EMPTY_SIGN    = '.';
static const QChar SPLITTER_SIGN = '^';

//-------------------------------------------------------------------------------------------------
Day7_2::Day7_2()
{
    QFile file("../../input/day7.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    file.close();

    executeTreeSplit(input);
    countPossibilities(input);

    return;

    QFile fileWrite("../../input/day7output.txt");
    if (!fileWrite.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&fileWrite);
    stream << input.join("\n");
    fileWrite.close();
}

//-------------------------------------------------------------------------------------------------
void Day7_2::executeTreeSplit(QStringList &tree)
{
    int startIndex = tree[0].indexOf(START_SIGN);
    tree[1].replace(startIndex, 1, BEAM_SIGN);

    for (int i = 0; i < tree.size() - 1; i++) {
        QString &topLine    = tree[i];
        QString &bottomLine = tree[i + 1];

        QList<int> beams = indexesForChar(topLine, BEAM_SIGN);

        for (const int &beamIndex : beams) {
            if (bottomLine[beamIndex] == EMPTY_SIGN)
                bottomLine.replace(beamIndex, 1, BEAM_SIGN);

            if (bottomLine[beamIndex] == SPLITTER_SIGN) {
                bottomLine.replace(beamIndex - 1, 1, BEAM_SIGN);
                bottomLine.replace(beamIndex + 1, 1, BEAM_SIGN);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
void Day7_2::countPossibilities(const QStringList &tree)
{
    // day7output.txt in vscode öffnen
    // HIER WEITERMACHEN
    QList<int> startingBeamIndexes = indexesForChar(tree.last(), BEAM_SIGN);
    qDebug() << startingBeamIndexes;
}

//-------------------------------------------------------------------------------------------------
QList<int> Day7_2::indexesForChar(const QString &line, const QChar &sign)
{
    QList<int> indexes;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == sign)
            indexes.append(i);
    }

    return indexes;
}
