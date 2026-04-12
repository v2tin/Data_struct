#pragma once
#include"inc.h"

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
