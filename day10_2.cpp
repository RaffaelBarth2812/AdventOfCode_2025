#include <algorithm>

#include <QDebug>
#include <QFile>

#include "day10_2.h"

static const QChar OFF = '.';

//-------------------------------------------------------------------------------------------------
Day10_2::Day10_2()
{
    qDebug() << processLine("[#.##] (0,1) (0,3) (2) {28,15,3,13}");
    return;
    QFile file("../../input/day10.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList input;

    while (!file.atEnd()) {
        QString line = file.readLine();
        input.append(line.simplified());
    }

    int buttonPresses = 0;
    for (const QString &line : input)
        buttonPresses += processLine(line);

    qDebug() << "Sum:" << buttonPresses;
}

//-------------------------------------------------------------------------------------------------
int Day10_2::processLine(const QString &line)
{
    // [.##.]   =   [ 0 1 1 0 ]     Matrix A

    // (3)      =   [ 0 0 0 1 ]     Button x1
    // (1,3)    =   [ 0 1 0 1 ]     Button x2
    // (2)      =   [ 0 0 1 0 ]     Button x3
    // (2,3)    =   [ 0 0 1 1 ]     Button x4
    // (0,2)    =   [ 1 0 1 0 ]     Button x5
    // (0,1)    =   [ 1 1 0 0 ]     Button x6

    //   Matrix A    +  Button x5  =   Matrix A     +  Button x4    = Finished
    // [ 0 1 1 0 ]   + [ 1 0 1 0 ] = [ 1 1 0 0 ]    + [ 0 0 1 1 ]   = [ 1 1 1 1 ]

    QStringList parts = line.split(" ");

    QString j = parts.takeLast();
    j = j.mid(1, j.size() - 2);
    QStringList joltagesTexts = j.split(",");

    QList<int> joltages;
    for (const QString &joltage : joltagesTexts)
        joltages.append(joltage.toInt());

    qDebug() << joltages;

    QString indicatorLightsText = parts.takeFirst().simplified();
    indicatorLightsText = indicatorLightsText.mid(1, indicatorLightsText.size() - 2);

    QBitArray indicatorLights(indicatorLightsText.size());
    for (int i = 0; i < indicatorLightsText.size(); i++)
        indicatorLights[i] = (indicatorLightsText.at(i) == OFF);

    QList<QBitArray> buttons;
    for (const QString &buttonText : parts) {
        const QStringList numbers = buttonText.mid(1, buttonText.size() - 2).split(",");

        buttons.append(QList<QBitArray>());

        QList<int> rawButtons;
        for (const QString &number : numbers)
            rawButtons.append(number.toInt());

        buttons.append(buttonToBinary(rawButtons, indicatorLightsText.size()));
    }

    return calculateButtonPresses(indicatorLights, buttons, joltages);
}

//-------------------------------------------------------------------------------------------------
QBitArray Day10_2::buttonToBinary(const QList<int> numbers, const int size) const
{
    QBitArray binary(size);
    for (const int n : numbers)
        binary[n] = 1;

    return binary;
}

//-------------------------------------------------------------------------------------------------
int Day10_2::calculateButtonPresses(QBitArray mask, QList<QBitArray> buttons, const QList<int> joltages) const
{
    QBitArray solution(mask.size(), true);
    int n = buttons.size();

    int bestCombination = n;
    for (int combination = 0; combination < (1 << n); combination++) {
        QBitArray current = mask;
        int presses = 0;

        for (int i = 0; i < n; i++) {
            if (combination & (1 << i)) {
                current ^= buttons[i];
                presses++;
            }
        }

        if (current == solution)
            bestCombination = std::min(bestCombination, presses);

    }

    return bestCombination;
}
