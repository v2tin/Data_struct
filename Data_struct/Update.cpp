#include "Update.h"
#include "State.h"
#include <chrono>

void UpdateSpeedByScore() {
    if (score >= 500) {
        tickInterval = 66.0;
    }
    else if (score >= 200) {
        tickInterval = 80.0;
    }
    else if (score >= 100) {
        tickInterval = 90.0;
    }
    else {
        tickInterval = baseTickInterval;
    }
}

void ResetUpdateTimer() {
    using namespace std::chrono;
    static auto& lastTime = []() -> auto& {
        static auto t = steady_clock::now();
        return t;
        }();
    lastTime = steady_clock::now();
}

void Update() {
    using namespace std::chrono;
    static auto lastTime = steady_clock::now();

    GameState currentState = GetGameState();

    switch (currentState) {
    case GameState::RUNNING: {
        auto currentTime = steady_clock::now();
        double elapsed = duration<double, milli>(currentTime - lastTime).count();

        if (elapsed >= tickInterval) {
            Logic();
            lastTime = currentTime;
        }
        break;
    }

    case GameState::PAUSED: {
        // 什么都不做，不写入文字，文字统一在 Render2 中显示
        break;
    }

    case GameState::GAME_OVER: {
        ToExit();
        break;
    }

    default:
        break;
    }
}