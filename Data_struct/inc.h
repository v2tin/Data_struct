#ifndef INC_H
#define INC_H

#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
using namespace std;

#define WIDTH 50
#define HEIGHT 20
#define endl "\n"

// 前向声明 State 相关（避免循环包含）
enum class GameState;
GameState GetGameState();

extern const char* SAVE_FILE;

extern HANDLE hOutput, hOutbuf;
extern COORD coord;
extern DWORD bytes;
extern bool BufferSwapFlag;
extern char ScreenData[HEIGHT + 5][WIDTH + 5];

struct Point {
    int x, y;
};

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

extern Point food;
extern vector<Point> snake;
extern eDirection dir;
extern bool gameOver;
extern int score;

// 速度系统变量
extern double tickInterval;
extern double baseTickInterval;

// 函数声明
void init();
void Logic();
void Input();
void Render();
void Render2();
void Show_DoubleBuffer();
void SaveGame();
bool LoadGame();
void ShowStartMenu();
void UpdateSpeedByScore();
void Update();
void ResetUpdateTimer();
void GameLoop();
void Clear();

#endif