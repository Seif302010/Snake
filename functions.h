#include <iostream>
#include <conio.h>
#include <thread>
#include <random>

#define N 8
#define BUFFER_SIZE 3
#define INITIAL_LENGTH 3

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

using namespace std;

extern const int MAP_AREA;
extern bool gameOver;
extern char e, sound, head, body, tail, food, inputBuffer[BUFFER_SIZE], Map[][N];
extern short headPos[2], tailPos[2], bufferedInput, length, turns[][4];

void clearScreen();
void mapPrinter();
void reprint();
void updatePosition(short hDir[2], short tDir[2], short (*&turnsFront)[4]);
void initializeVariables();
bool isValidInput(const char &input, const char &previousInput);
void changeDirection(const char &input, short headDir[2], short (*&turnsFront)[4]);
char reverseInput(const char &input);
void generateFood();

#endif // FUNCTIONS_H_INCLUDED
