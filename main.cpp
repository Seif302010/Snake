#include "functions.h"

using namespace std;

char *bufferFront = inputBuffer;
short (*turnsFront)[4] = turns;


int main()
{
    short headDir[2] = {0, 1}, tailDir[2] = {headDir[0], headDir[1]};
    Initialize_variables();
    char newInput, currentInput = *bufferFront;
    chrono::milliseconds delay(200);
    mapPrinter();
    while (true)
    {
        this_thread::sleep_for(delay);
        while (kbhit())
        {
            newInput = tolower(getch());
            if (newInput == 'p')
            {
                cout << "game paused" << endl;
                char unpause = '0';
                while (unpause != 'p')
                {
                    if (kbhit())
                        unpause = tolower(getch());
                }
                reprint();
                this_thread::sleep_for(delay);
                if (kbhit())
                {
                    newInput = tolower(getch());
                }
            }
            if (bufferedInput < BUFFER_SIZE && isValidInput(newInput, currentInput))
            {
                inputBuffer[inputIndex] = newInput;
                bufferedInput++;
                inputIndex = (inputIndex + 1) % BUFFER_SIZE;
            }
        }
        if (bufferedInput > 0)
        {
            currentInput = *bufferFront;
            bufferFront = &inputBuffer[(bufferFront - inputBuffer + 1) % BUFFER_SIZE];
            bufferedInput--;

            changeDirection(currentInput, headDir);
        }
        updatePosition(headDir, tailDir,turnsFront);
        reprint();
    }
    return 0;
}
