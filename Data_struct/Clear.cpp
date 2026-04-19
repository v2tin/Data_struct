#include "Clear.h"
#include "inc.h"

void Clear() {
    Show_DoubleBuffer();
    Sleep(100);
    while (!_kbhit()) {
        Sleep(100);
    }

    CloseHandle(hOutput);
    CloseHandle(hOutbuf);
}