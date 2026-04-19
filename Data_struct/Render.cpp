#include "Render.h"
#include"State.h"

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

void Render2() {
    int i, j;
    int curLine = 0;

    // 绘制上边界
    for (j = 0; j < WIDTH + 2; j++) {
        ScreenData[curLine][j] = '#';
    }
    curLine++;

    // 绘制游戏区域
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH + 2; j++) {
            if (j == 0 || j == WIDTH + 1) {
                ScreenData[curLine + i][j] = '#';
            }
            else if (i == snake[0].y && j == snake[0].x) {
                ScreenData[curLine + i][j] = 'O';
            }
            else if (i == food.y && j == food.x) {
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

    // 绘制下边界
    for (j = 0; j < WIDTH + 2; j++) {
        ScreenData[curLine + i][j] = '#';
    }
    curLine++;

    // ========== 根据游戏状态显示底部信息（统一在此处理）==========
    GameState currentState = GetGameState();

    if (currentState == GameState::PAUSED) {
        // 暂停状态：只显示一行暂停文字
        sprintf(ScreenData[curLine + i], "游戏暂停 - 按 P 键继续");
        // 清空下一行（避免残留）
        if (curLine + i + 1 < HEIGHT + 5) {
            sprintf(ScreenData[curLine + i + 1], "%-*s", WIDTH + 2, "");
        }
    }
    else if (currentState == GameState::RUNNING) {
        // 运行状态：显示得分
        sprintf(ScreenData[curLine + i], "游戏得分: %d", score);
        // 清空下一行
        if (curLine + i + 1 < HEIGHT + 5) {
            sprintf(ScreenData[curLine + i + 1], "%-*s", WIDTH + 2, "");
        }
    }
    else if (currentState == GameState::GAME_OVER || gameOver) {
        // 游戏结束状态
        sprintf(ScreenData[curLine + i], "GAME OVER");
        sprintf(ScreenData[curLine + i + 1], "游戏结束! 最终得分: %d", score);
    }
}


void Show_DoubleBuffer() {
    int i;
    Render2();  // 每帧都会重新渲染，包括暂停文字
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