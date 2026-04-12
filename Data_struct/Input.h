#pragma
#include"inc.h"
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