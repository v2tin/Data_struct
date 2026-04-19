#include "Input.h"
#include "State.h"
#include <deque>

void Input() {
    static std::deque<char> keyBuffer;

    keyBuffer.clear();

    while (_kbhit()) {
        char key = _getch();

        // 全局功能键（任何非 GAME_OVER 状态都可用，除了已退出）
        if (key == 'q') {
            if (GetGameState() == GameState::RUNNING || GetGameState() == GameState::PAUSED) {
                SaveGame();
                Render2();
                sprintf(ScreenData[HEIGHT + 3], "已保存存档，按任意键退出");
                Show_DoubleBuffer();
                while (!_kbhit()) Sleep(100);
                _getch();
                ToExit();
                gameOver = true;  // 保持兼容
                return;
            }
        }
        else if (key == 'x') {
            if (GetGameState() == GameState::RUNNING || GetGameState() == GameState::PAUSED) {
                ToExit();
                gameOver = true;  // 保持兼容
                return;
            }
        }
        // 暂停/继续键（P）
        else if (key == 'p') {
            if (GetGameState() == GameState::RUNNING || GetGameState() == GameState::PAUSED) {
                TogglePause();
                return;
            }
        }

        // 只有 RUNNING 状态才处理方向键
        if (!CanProcessDirection()) {
            continue;
        }

        // 方向键处理（只有 RUNNING 状态才会执行到这里）
        if (key == 'a' || key == 'd' || key == 'w' || key == 's') {
            keyBuffer.push_back(key);
        }
    }

    // 方向键处理逻辑（只有在 RUNNING 状态且有按键时执行）
    if (!CanProcessDirection() || keyBuffer.empty()) {
        return;
    }

    eDirection newDir = dir;
    for (auto it = keyBuffer.begin(); it != keyBuffer.end(); ++it) {
        char key = *it;
        switch (key) {
        case 'a':
            if (newDir != RIGHT) newDir = LEFT;
            break;
        case 'd':
            if (newDir != LEFT) newDir = RIGHT;
            break;
        case 'w':
            if (newDir != DOWN) newDir = UP;
            break;
        case 's':
            if (newDir != UP) newDir = DOWN;
            break;
        }
    }
    dir = newDir;
}