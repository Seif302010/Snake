#include "functions.h"

char currentInput, newInput, *bufferFront, *bufferRear;
short headDir[2], tailDir[2], (*turnsFront)[4], (*turnsRear)[4];

void moveCursorTo(const short &row, const short &column)
{
#ifdef _WIN32
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {static_cast<SHORT>(column), static_cast<SHORT>(row)});
#else
    cout << "\033[" << (row + 1) << ";" << (column + 1) << "H";
#endif
}

void clearFromCursor()
{
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellsWritten;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputCharacter(hConsole, (TCHAR)' ', csbi.dwSize.X * csbi.dwSize.Y, csbi.dwCursorPosition, &cellsWritten);
#else
    cout << "\033[J";
#endif
}

void updateCells(short oldTailPos[2], short oldHeadPos[2])
{
    if (oldTailPos[0] != tailPos[0] || oldTailPos[1] != tailPos[1])
    {
        moveCursorTo(oldTailPos[0], oldTailPos[1] * 2);
        cout << e;
        moveCursorTo(tailPos[0], tailPos[1] * 2);
        cout << tail;
    }
    moveCursorTo(oldHeadPos[0], oldHeadPos[1] * 2);
    cout << body;
    moveCursorTo(headPos[0], headPos[1] * 2);
    cout << head;
    if (newFood)
    {
        moveCursorTo(foodPos[0], foodPos[1] * 2);
        cout << food;
        newFood = false;
    }
    moveCursorTo(N, 0);
    clearFromCursor();
    cout << endl
         << endl;
}

chrono::milliseconds delay(200);
int main()
{
    short oldTailPos[2], oldHeadPos[2];
    char replay = 'y';
    while (replay == 'y')
    {
        turnsFront = turns;
        turnsRear = turns;
        bufferFront = inputBuffer;
        bufferRear = inputBuffer;
        headDir[0] = 0;
        headDir[1] = 1;
        updateArray(tailDir, headDir, 2);
        updateArray(oldHeadPos, headPos, 2);
        updateArray(oldTailPos, tailPos, 2);
        initializeVariables();
        currentInput = *bufferFront, newInput = *bufferFront;
        generateFood();
        newFood = false;
        reprint();
        while (true)
        {
            this_thread::sleep_for(delay);
            currentInput = bufferedInput ? *bufferRear : currentInput;
            while (kbhit())
            {
                newInput = tolower(getch());
                if (newInput == 'p')
                {
                    cout << "game paused" << endl;
                    currentInput = bufferedInput % 2 ? reverseInput(currentInput) : currentInput;
                    bufferedInput = 0;
                    bufferFront = inputBuffer;
                    bufferRear = inputBuffer;
                    newInput = '0';
                    while (newInput != 'p')
                        if (kbhit())
                            newInput = tolower(getch());
                    moveCursorTo(N, 0);
                    clearFromCursor();
                    cout << endl
                         << endl;
                    this_thread::sleep_for(delay);
                    if (kbhit())
                        newInput = tolower(getch());
                }
                if (bufferedInput < BUFFER_SIZE && isValidInput(newInput, currentInput))
                {
                    *bufferRear = newInput;
                    bufferedInput++;
                    bufferRear = &inputBuffer[(bufferRear - inputBuffer + 1) % BUFFER_SIZE];
                    currentInput = newInput;
                }
            }
            if (bufferedInput > 0)
            {
                currentInput = *bufferFront;
                bufferFront = &inputBuffer[(bufferFront - inputBuffer + 1) % BUFFER_SIZE];
                bufferedInput--;

                changeDirection(currentInput, headDir, turnsRear);
            }

            updateArray(oldHeadPos, headPos, 2);
            updateArray(oldTailPos, tailPos, 2);
            updatePosition(headDir, tailDir, turnsFront);
            updateCells(oldTailPos, oldHeadPos);
            if (gameOver)
            {
                cout << sound << (length == MAP_AREA ? "You Win" : "GAME OVER") << endl;
                break;
            }
        }
        cout << "Play again? (y,n)" << endl;
        while (true)
        {
            replay = tolower(getch());
            if (replay == '\n')
                continue;
            else if (replay == 'n' || replay == 'y')
                break;
        }
    }
    return 0;
}
