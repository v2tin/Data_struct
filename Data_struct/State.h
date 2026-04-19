#ifndef STATE_H
#define STATE_H

enum class GameState {
    MENU,
    RUNNING,
    PAUSED,
    GAME_OVER,
    EXIT
};

// 获取/设置当前状态
GameState GetGameState();
void SetGameState(GameState newState);

// 状态转换函数
void ToRunning();
void ToPaused();
void ToGameOver();
void ToExit();

// 检查状态是否正在运行中（RUNNING）
bool IsRunning();

// 检查状态是否可处理方向输入（只有 RUNNING 状态可以）
bool CanProcessDirection();

// 处理暂停键（P）
void TogglePause();

#endif