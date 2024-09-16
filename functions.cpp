#include "functions.h"

const int MAP_AREA = N * N;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<short> distribution(0, N - 1);

bool gameOver = false, newFood = true;
char e = 254, sound = 7, head = '$', body = '*', tail = body, food = '+', inputBuffer[BUFFER_SIZE], Map[N][N];
short headPos[2] = {0, 0}, tailPos[2] = {0, 0}, foodPos[2], bufferedInput = 0, length = INITIAL_LENGTH, turns[MAP_AREA][4];

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void mapPrinter()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
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
void updateArray(short arr1[], short arr2[], short n)
{
    for (short i = 0; i < n; i++)
        arr1[i] = arr2[i];
}

void updatePosition(short hDir[2], short tDir[2], short (*&turnsFront)[4])
{
    short newHead[2] = {short((headPos[0] + hDir[0] + N) % N), short((headPos[1] + hDir[1] + N) % N)};
    if ((*turnsFront)[0] < N && tailPos[0] == (*turnsFront)[0] && tailPos[1] == (*turnsFront)[1])
    {
        tDir[(*turnsFront)[2]] = (*turnsFront)[3];
        tDir[((*turnsFront)[2] + 1) % 2] = 0;
        (*turnsFront)[0] = N;
        (*turnsFront)[1] = N;
        turnsFront = &turns[(turnsFront - turns + 1) % MAP_AREA];
    }
    short newTail[2] = {short((tailPos[0] + tDir[0] + N) % N), short((tailPos[1] + tDir[1] + N) % N)};
    Map[headPos[0]][headPos[1]] = body;
    Map[tailPos[0]][tailPos[1]] = e;
    if (Map[newHead[0]][newHead[1]] == food)
    {
        updateArray(newTail, tailPos, 2);
        Map[tailPos[0]][tailPos[1]] = tail;
        length++;
        generateFood();
    }
    else if (Map[newHead[0]][newHead[1]] != e || length == MAP_AREA)
        gameOver = true;
    Map[newTail[0]][newTail[1]] = tail;
    Map[newHead[0]][newHead[1]] = head;
    updateArray(headPos, newHead, 2);
    updateArray(tailPos, newTail, 2);
}

void initializeVariables()
{
    short initial[2] = {0, 0};
    updateArray(headPos, initial, 2);
    updateArray(tailPos, initial, 2);
    bufferedInput = 0;
    length = INITIAL_LENGTH;
    gameOver = false;
    newFood = true;
    for (int i = 0; i < N; i++)
    {
        if (i < BUFFER_SIZE)
            inputBuffer[i] = e;
        for (int j = 0; j < N; j++)
            Map[i][j] = e;
    }
    headPos[1] = length - 1;
    for (int i = 0; i < length; i++)
        Map[headPos[0]][i] = body;
    for (int i = 0; i < MAP_AREA; i++)
    {
        turns[i][0] = N;
        turns[i][1] = N;
    }

    Map[headPos[0]][headPos[1]] = head;
    inputBuffer[0] = 'd';
}

bool isVertical(const char &input)
{
    return input == 'w' || input == 's';
}

bool isHorizontal(const char &input)
{
    return input == 'a' || input == 'd';
}

bool isValidInput(const char &input, const char &previousInput)
{
    return (isVertical(previousInput) && isHorizontal(input)) ||
           (isHorizontal(previousInput) && isVertical(input));
}

void changeDirection(const char &input, short headDir[2], short (*&turnsRear)[4])
{
    headDir[0] = input == 'w' ? -1 : input == 's' ? 1
                                                  : 0;
    headDir[1] = input == 'a' ? -1 : input == 'd' ? 1
                                                  : 0;
    (*turnsRear)[0] = headPos[0];
    (*turnsRear)[1] = headPos[1];
    (*turnsRear)[2] = headDir[0] ? 0 : 1;
    (*turnsRear)[3] = headDir[0] ? headDir[0] : headDir[1];
    turnsRear = &turns[(turnsRear - turns + 1) % MAP_AREA];
}

char reverseInput(const char &input)
{
    return isVertical(input) ? 'a' : 'w';
}

void generateFood()
{
    short x = distribution(gen), y = distribution(gen);
    newFood = false;
    for (short i = 0; i < N; i++)
    {
        if (newFood)
            break;
        short X = (x + i) % N;
        for (short j = 0; j < N; j++)
        {
            short Y = (y + j) % N;
            if (Map[X][Y] == e)
            {
                short newFoodPos[2] = {X, Y};
                Map[X][Y] = food;
                updateArray(foodPos, newFoodPos, 2);
                newFood = true;
                break;
            }
        }
    }
}
