#include "GameLoop.h"
#include "inc.h"

void GameLoop() {
    while (!gameOver) {
        Input();
        Update();
        Show_DoubleBuffer();
    }
}