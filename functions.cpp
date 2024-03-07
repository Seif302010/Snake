#include "functions.h"

const short n = 8, BUFFER_SIZE = 5;

char e = 254, sound = 7, head = '$', body = '*', inputBuffer[BUFFER_SIZE], Map[n][n];
short headPos[2] = {0, 0}, tailPos[2] = {0, 0}, bufferedInput = 0, inputIndex = 0, length = 3, turns[n * n][4], turnIndex = 0;

void clearScreen()
{
    system("cls");
}

void mapPrinter()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << Map[i][j] << " ";
        cout << endl;
    }
    cout << endl
         << endl;
}

void reprint()
{
    clearScreen();
    mapPrinter();
}

void updatePosition(short hDir[2], short tDir[2], short (*&turnsFront)[4])
{
    short newHeadX = (headPos[0] + hDir[0] + n) % n, newHeadY = (headPos[1] + hDir[1] + n) % n;
    if ((*turnsFront)[0] < n && tailPos[0] == (*turnsFront)[0] && tailPos[1] == (*turnsFront)[1])
    {
        tDir[(*turnsFront)[2]] = (*turnsFront)[3];
        tDir[((*turnsFront)[2] + 1) % 2] = 0;
        (*turnsFront)[0] = n;
        (*turnsFront)[1] = n;
        turnsFront = &turns[(turnsFront - turns + 1) % (n * n)];
    }
    short newTailX = (tailPos[0] + tDir[0] + n) % n, newTailY = (tailPos[1] + tDir[1] + n) % n;
    Map[newTailX][newTailY] = Map[tailPos[0]][tailPos[1]];
    Map[tailPos[0]][tailPos[1]] = e;
    Map[newHeadX][newHeadY] = Map[headPos[0]][headPos[1]];
    Map[headPos[0]][headPos[1]] = body;
    headPos[0] = newHeadX;
    headPos[1] = newHeadY;
    tailPos[0] = newTailX;
    tailPos[1] = newTailY;
}

void Initialize_variables()
{
    for (int i = 0; i < n; i++)
    {
        if (i < BUFFER_SIZE)
            inputBuffer[i] = e;
        for (int j = 0; j < n; j++)
            Map[i][j] = e;
    }
    headPos[1] = length - 1;
    for (int i = 0; i < length; i++)
        Map[headPos[0]][i] = body;
    for (int i = 0; i < n * n; i++)
    {
        turns[i][0] = n;
        turns[i][1] = n;
    }

    Map[headPos[0]][headPos[1]] = head;
    inputBuffer[0] = 'd';
}

bool isValidInput(const char &input, const char &previousInput)
{
    if (previousInput == 'w' || previousInput == 's')
        return input == 'a' || input == 'd';
    else if (previousInput == 'a' || previousInput == 'd')
        return input == 'w' || input == 's';
    return false;
}

void changeDirection(const char &input, short headDir[2])
{
//    if (isValidInput(input, previousInput))
//    {
        headDir[0] = input == 'w' ? -1 : input == 's' ? 1 : 0;
        headDir[1] = input == 'a' ? -1 : input == 'd' ? 1 : 0;
        turns[turnIndex][0] = headPos[0];
        turns[turnIndex][1] = headPos[1];
        turns[turnIndex][2] = headDir[0] != 0 ? 0 : 1;
        turns[turnIndex][3] = headDir[0] != 0 ? headDir[0] : headDir[1];
        turnIndex = (turnIndex + 1) % (n * n);
//    }
}
