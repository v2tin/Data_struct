#include "inc.h"
#include "GameLoop.h"
#include "State.h"

const char* SAVE_FILE = "save.txt";

HANDLE hOutput, hOutbuf;
COORD coord = { 0,0 };
DWORD bytes = 0;
bool BufferSwapFlag = false;
char ScreenData[HEIGHT + 5][WIDTH + 5];

Point food;
vector<Point> snake;
eDirection dir;
bool gameOver;
int score;

double tickInterval = 100.0;
double baseTickInterval = 100.0;

int main()
{
    // MENU 状态
    ShowStartMenu();

    // 菜单选择后，进入 RUNNING 状态
    ToRunning();

    // 进入游戏主循环
    GameLoop();

    // 游戏结束后的清理
    Clear();
    return 0;
}