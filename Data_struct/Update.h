#ifndef UPDATE_H
#define UPDATE_H

#include "inc.h"

void UpdateSpeedByScore();
void Update();
void ResetUpdateTimer();

// 新增：设置暂停提示文字（在 Render2 中使用）
void SetPausedMessage(bool isPaused);

#endif