#include "functions.h"

using namespace std;

char *bufferFront = inputBuffer,*bufferRear = inputBuffer;
short (*turnsFront)[4] = turns,(*turnsRear)[4] = turns;


int main()
{
    short headDir[2] = {0, 1}, tailDir[2] = {headDir[0], headDir[1]};
    Initialize_variables();
    char currentInput = *bufferFront, newInput = *bufferFront;
    chrono::milliseconds delay(200);
    mapPrinter();
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
                currentInput = bufferedInput ? reverseInput(currentInput) : currentInput;
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
//                if(bufferedInput == BUFFER_SIZE){
//                    clearScreen();
//                    cout<<"the buffer is full "<<endl;
//                    while(true);
//                }
            }
        }
        if (bufferedInput > 0)
        {
            currentInput = *bufferFront;
            bufferFront = &inputBuffer[(bufferFront - inputBuffer + 1) % BUFFER_SIZE];
            bufferedInput--;

            changeDirection(currentInput, headDir,turnsRear);
        }
        updatePosition(headDir, tailDir,turnsFront);
        reprint();
    }
    return 0;
}
