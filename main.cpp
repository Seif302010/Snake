#include "functions.h"

using namespace std;

char *bufferFront = inputBuffer;
short (*turnsFront)[4] = turns;


int main()
{
    short headDir[2] = {0, 1}, tailDir[2] = {headDir[0], headDir[1]};
    Initialize_variables();
    char input = *bufferFront;
    chrono::milliseconds delay(200);
    while (true)
    {
        reprint();
        while (kbhit())
        {
            char temp = tolower(getch());
            if (temp == 'p')
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
                    temp = tolower(getch());
                }
            }
            if (bufferedInput < BUFFER_SIZE && isValidInput(temp, input))
            {
                inputBuffer[inputIndex] = temp;
                bufferedInput++;
                inputIndex = (inputIndex + 1) % BUFFER_SIZE;
            }
        }
        if (bufferedInput > 0)
        {
            input = *bufferFront;
            bufferFront = &inputBuffer[(bufferFront - inputBuffer + 1) % BUFFER_SIZE];
            bufferedInput--;

            changeDirection(input, headDir);
        }
        updatePosition(headDir, tailDir,turnsFront);

        this_thread::sleep_for(delay);
    }
    return 0;
}
