#pragma once
#include"inc.h"

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