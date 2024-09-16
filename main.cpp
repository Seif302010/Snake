#include "functions.h"

char currentInput, newInput, *bufferFront, *bufferRear;
short headDir[2], tailDir[2], (*turnsFront)[4], (*turnsRear)[4];

chrono::milliseconds delay(200);
int main()
{
    char replay = 'y';
    while (replay == 'y')
    {
        turnsFront = turns;
        turnsRear = turns;
        bufferFront = inputBuffer;
        bufferRear = inputBuffer;
        headDir[0] = 0;
        headDir[1] = 1;
        tailDir[0] = headDir[0];
        tailDir[1] = headDir[1];
        initializeVariables();
        currentInput = *bufferFront, newInput = *bufferFront;
        generateFood();
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
                    reprint();
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
            updatePosition(headDir, tailDir, turnsFront);
            reprint();
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
