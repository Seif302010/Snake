#include <iostream>
#include <thread>
#include <random>
#include <conio.h>

#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#define SQUARE string(1, char(254)).c_str()
#else
#define CLEAR_SCREEN "clear"
#define SQUARE string("\u25a0").c_str()
#define getch() console.getch()
#define kbhit() console.kbhit()
#endif

#define N 8
#define BUFFER_SIZE 3
#define INITIAL_LENGTH 3

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

using namespace std;

extern const int MAP_AREA;
extern bool gameOver, newFood;
extern char e, sound, head, body, tail, food, inputBuffer[BUFFER_SIZE], Map[][N];
extern short headPos[2], tailPos[2], foodPos[2], bufferedInput, length, turns[][4];

void moveCursorTo(const short &row, const short &column);
void clearFromCursor();
void clearScreen();
void mapPrinter();
void reprint();
void updateArray(short arr1[], short arr2[], short n);
void updatePosition(short hDir[2], short tDir[2], short (*&turnsFront)[4]);
void initializeVariables();
bool isValidInput(const char &input, const char &previousInput);
void changeDirection(const char &input, short headDir[2], short (*&turnsFront)[4]);
char reverseInput(const char &input);
void generateFood();

#endif // FUNCTIONS_H_INCLUDED
