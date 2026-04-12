#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
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

void init() {
    // 如果已经创建过，先关闭旧的句柄（避免泄漏）
    if (hOutput) CloseHandle(hOutput);
    if (hOutbuf) CloseHandle(hOutbuf);

    hOutbuf = CreateConsoleScreenBuffer(
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    hOutput = CreateConsoleScreenBuffer(
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    // 隐藏两个缓冲区的光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = false;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutput, &cci);
    SetConsoleCursorInfo(hOutbuf, &cci);

    gameOver = false;
    score = 0;
    dir = STOP;
    snake.clear();
    snake.push_back({ WIDTH / 2, HEIGHT / 2 });
    food = { rand() % WIDTH + 1, rand() % HEIGHT + 1 };
}

void Logic() {
    if (snake[0].x < 1 || snake[0].x > WIDTH || snake[0].y < 1 || snake[0].y > HEIGHT) {
        gameOver = true;
        return;
    }
    for (int i = 1; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = true;
            return;
        }
    }
    if (snake[0].x == food.x && snake[0].y == food.y) {
        score += 10;
        food = { rand() % WIDTH + 1, rand() % HEIGHT + 1 };
        snake.push_back({ snake[snake.size() - 1].x, snake[snake.size() - 1].y });
    }
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    switch (dir) {
    case LEFT: snake[0].x--; break;
    case RIGHT: snake[0].x++; break;
    case UP: snake[0].y--; break;
    case DOWN: snake[0].y++; break;
    default: break;
    }
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
        {
            if (dir != RIGHT)
                dir = LEFT;
            break;
        }
        case 'd':
        {
            if (dir != LEFT)
                dir = RIGHT;
            break;
        }
        case 'w':
        {
            if (dir != DOWN) {
                dir = UP;
            }
            break;
        }
        case 's':
        {
            if (dir != UP) dir = DOWN;
            break;
        }
        case 'q':
        {
            SaveGame();
            Render2();
            sprintf(ScreenData[HEIGHT + 3], "已保存存档，按任意键退出");
            Show_DoubleBuffer();
            while (!_kbhit()) Sleep(100);
            _getch();
            gameOver = true;
            return;
        }
        break;
        case 'x': gameOver = true; break;
        default: break;
        }
    }
}

void Render() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int textColor = 0x86;
    SetConsoleTextAttribute(h, textColor);
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            if (j == 0 || j == WIDTH + 1) {
                textColor = 0x86;
                SetConsoleTextAttribute(h, textColor);
                cout << "#";
            }
            else if (i == snake[0].y && j == snake[0].x) {
                textColor = 0x8a;
                SetConsoleTextAttribute(h, textColor);
                cout << "O";
            }
            else if (i == food.y && j == food.x)
            {
                textColor = 0x84;
                SetConsoleTextAttribute(h, textColor);
                cout << "F";
            }
            else {
                bool isBody = false;
                for (int k = 1; k < snake.size(); k++) {
                    if (snake[k].x == j && snake[k].y == i) {
                        textColor = 0x8a;
                        SetConsoleTextAttribute(h, textColor);
                        cout << "o";
                        isBody = true;
                        break;
                    }
                }
                if (!isBody) cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;
    cout << "游戏得分: " << score << endl;
}

void Render2()
{
    int i, j;
    int curLine = 0;

    for (j = 0; j < WIDTH + 2; j++) {
        ScreenData[curLine][j] = '#';
    }
    curLine++;

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH + 2; j++) {
            if (j == 0 || j == WIDTH + 1) {
                ScreenData[curLine + i][j] = '#';
            }
            else if (i == snake[0].y && j == snake[0].x) {
                ScreenData[curLine + i][j] = 'O';
            }
            else if (i == food.y && j == food.x)
            {
                ScreenData[curLine + i][j] = 'F';
            }
            else {
                bool isBody = false;
                for (int k = 1; k < snake.size(); k++) {
                    if (snake[k].x == j && snake[k].y == i) {
                        ScreenData[curLine + i][j] = 'o';
                        isBody = true;
                        break;
                    }
                }
                if (!isBody) ScreenData[curLine + i][j] = ' ';
            }
        }
    }
    for (j = 0; j < WIDTH + 2; j++) ScreenData[curLine + i][j] = '#';
    curLine++;
    if (!gameOver) sprintf(ScreenData[curLine + i], "游戏得分: %d", score);
    else {
        sprintf(ScreenData[curLine + i], "GAME OVER");
        sprintf(ScreenData[curLine + i + 1], "游戏结束! 最终得分: %d", score);
    }
}

void Show_DoubleBuffer()
{
    int i;
    Render2();
    if (BufferSwapFlag == false) {
        BufferSwapFlag = true;
        for (i = 0; i < HEIGHT + 5; i++) {
            coord.Y = i;
            WriteConsoleOutputCharacterA(hOutbuf, ScreenData[i], WIDTH + 2, coord, &bytes);
        }
        SetConsoleActiveScreenBuffer(hOutbuf);
    }
    else {
        BufferSwapFlag = false;
        for (i = 0; i < HEIGHT + 5; i++) {
            coord.Y = i;
            WriteConsoleOutputCharacterA(hOutput, ScreenData[i], WIDTH + 2, coord, &bytes);
        }
        SetConsoleActiveScreenBuffer(hOutput);
    }
}

void SaveGame() {
    FILE* fp = fopen(SAVE_FILE, "w");
    if (fp == NULL) return;

    int len = snake.size();
    fprintf(fp, "%d\n", len);

    for (int i = 0; i < len; i++) {
        fprintf(fp, "%d %d\n", snake[i].x, snake[i].y);
    }

    char dirChar;
    switch (dir) {
    case LEFT:  dirChar = 'L'; break;
    case RIGHT: dirChar = 'R'; break;
    case UP:    dirChar = 'U'; break;
    case DOWN:  dirChar = 'D'; break;
    default:    dirChar = 'S'; break;
    }
    fprintf(fp, "%c\n", dirChar);

    fprintf(fp, "%d %d\n", food.x, food.y);
    fprintf(fp, "%d\n", score);

    fclose(fp);
}

bool LoadGame() {
    FILE* fp = fopen(SAVE_FILE, "r");
    if (fp == NULL) return false;

    snake.clear();

    int len;
    fscanf(fp, "%d\n", &len);

    for (int i = 0; i < len; i++) {
        Point p;
        fscanf(fp, "%d %d\n", &p.x, &p.y);
        snake.push_back(p);
    }

    char dirChar;
    fscanf(fp, "%c\n", &dirChar);
    switch (dirChar) {
    case 'L': dir = LEFT; break;
    case 'R': dir = RIGHT; break;
    case 'U': dir = UP; break;
    case 'D': dir = DOWN; break;
    default:  dir = STOP; break;
    }

    fscanf(fp, "%d %d\n", &food.x, &food.y);
    fscanf(fp, "%d\n", &score);

    fclose(fp);

    return true;
}

void ShowStartMenu() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 0x86);
    cout << "=====================================" << endl;
    cout << "          贪吃蛇 - 存档系统          " << endl;
    cout << "=====================================" << endl;

    FILE* fp = fopen(SAVE_FILE, "r");
    if (fp == NULL) {
        cout << "没有可用的存档，将开始新游戏。" << endl;
        cout << "按任意键继续..." << endl;
        _getch();
        return;  // 直接返回，main 中会调用 init() 开始新游戏
    }
    fclose(fp);

    cout << "检测到存档文件。" << endl;
    cout << "1. 继续上个存档" << endl;
    cout << "2. 重新开始游戏" << endl;
    cout << "请选择 (1 或 2): ";

    char choice = _getch();
    cout << choice << endl;

    if (choice == '1') {
        // 先初始化屏幕缓冲区，再加载数据
        init();  // 创建屏幕缓冲区
        if (!LoadGame()) {
            cout << "加载存档失败，将开始新游戏。" << endl;
            // 加载失败，数据已经是 init() 的新游戏状态，无需额外操作
        }
        else {
            cout << "加载存档成功！按任意键开始游戏..." << endl;
        }
    }
    else {
        cout << "重新开始新游戏。按任意键继续..." << endl;
        init();  // 初始化新游戏
    }
    _getch();
}

int main()
{
    ShowStartMenu();   // 内部已经根据选择调用了 init() 或 init()+LoadGame()

    while (!gameOver) {
        Show_DoubleBuffer();
        Input();
        Logic();
        Sleep(100);
    }

    Show_DoubleBuffer();
    Sleep(100);
    while (!_kbhit()) {
        Sleep(100);
    }

    CloseHandle(hOutput);
    CloseHandle(hOutbuf);

    return 0;
}