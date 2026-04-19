#include "Logic.h"
#include "Update.h"
#include "State.h"

void init() {
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

    tickInterval = 100.0;
    baseTickInterval = 100.0;

    ResetUpdateTimer();
}

void Logic() {
    if (snake[0].x < 1 || snake[0].x > WIDTH || snake[0].y < 1 || snake[0].y > HEIGHT) {
        gameOver = true;
        ToGameOver();  // ×´Ì¬×ª»»
        return;
    }

    for (int i = 1; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = true;
            ToGameOver();  // ×´Ì¬×ª»»
            return;
        }
    }

    bool ateFood = (snake[0].x == food.x && snake[0].y == food.y);

    if (ateFood) {
        int oldScore = score;
        score += 10;
        food = { rand() % WIDTH + 1, rand() % HEIGHT + 1 };
        snake.push_back({ snake[snake.size() - 1].x, snake[snake.size() - 1].y });

        int oldLevel = (oldScore >= 500) ? 4 : (oldScore >= 200) ? 3 : (oldScore >= 100) ? 2 : 1;
        int newLevel = (score >= 500) ? 4 : (score >= 200) ? 3 : (score >= 100) ? 2 : 1;

        if (newLevel != oldLevel) {
            UpdateSpeedByScore();
        }
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