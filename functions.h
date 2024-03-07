#include <iostream>
#include <conio.h>
#include <thread>

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

using namespace std;

extern const short n, BUFFER_SIZE;

extern char e, sound, head, body, inputBuffer[5], Map[][8];
extern short headPos[2], tailPos[2], bufferedInput, inputIndex, length, turns[][4], turnIndex;

void clearScreen();
void mapPrinter();
void reprint();
void updatePosition(short hDir[2], short tDir[2], short (*&turnsFront)[4]);
void Initialize_variables();
bool isValidInput(const char &input, const char &previousInput);
void changeDirection(const char &input, short headDir[2]);

#endif // FUNCTIONS_H_INCLUDED
