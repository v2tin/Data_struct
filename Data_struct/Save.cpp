#include "Save.h"
#include "Update.h"

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

    // 保存当前速度档位
    fprintf(fp, "%.1f\n", tickInterval);

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

    // 加载速度档位（兼容旧存档）
    if (fscanf(fp, "%lf\n", &tickInterval) != 1) {
        // 旧存档没有速度信息，根据当前分数重新计算
        if (score >= 500) tickInterval = 66.0;
        else if (score >= 200) tickInterval = 80.0;
        else if (score >= 100) tickInterval = 90.0;
        else tickInterval = 100.0;
    }
    baseTickInterval = 100.0;

    fclose(fp);

    // 加载存档成功后重置计时器，避免第一帧立即触发多次更新
    ResetUpdateTimer();

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
        return;
    }
    fclose(fp);

    cout << "检测到存档文件。" << endl;
    cout << "1. 继续上个存档" << endl;
    cout << "2. 重新开始游戏" << endl;
    cout << "请选择 (1 或 2): ";

    char choice = _getch();
    cout << choice << endl;

    if (choice == '1') {
        init();
        if (!LoadGame()) {
            cout << "加载存档失败，将开始新游戏。" << endl;
        }
        else {
            cout << "加载存档成功！按任意键开始游戏..." << endl;
        }
    }
    else {
        cout << "重新开始新游戏。按任意键继续..." << endl;
        init();
    }
    _getch();
}