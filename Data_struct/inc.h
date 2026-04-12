#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include"Input.h"
#include"Logic.h"
#include"Render.h"
#include"Save.h"
using namespace std;

#define WIDTH 50
#define HEIGHT 20
#define endl "\n"

const char* SAVE_FILE = "save.txt";

HANDLE hOutput, hOutbuf;
COORD coord = { 0,0 };
DWORD bytes = 0;
bool BufferSwapFlag = false;
char ScreenData[HEIGHT + 5][WIDTH + 5];

struct Point {
    int x, y;
};
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
Point food;
vector<Point> snake;
eDirection dir;
bool gameOver;
int score;