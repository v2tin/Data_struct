#pragma once
#include"inc.h"

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