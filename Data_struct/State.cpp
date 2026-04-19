#include "State.h"
#include "inc.h"
#include "Save.h"

static GameState currentState = GameState::MENU;

GameState GetGameState() {
    return currentState;
}

void SetGameState(GameState newState) {
    currentState = newState;
}

void ToRunning() {
    currentState = GameState::RUNNING;
}

void ToPaused() {
    if (currentState == GameState::RUNNING) {
        currentState = GameState::PAUSED;
    }
}

void ToGameOver() {
    if (currentState == GameState::RUNNING || currentState == GameState::PAUSED) {
        currentState = GameState::GAME_OVER;
    }
}

void ToExit() {
    currentState = GameState::EXIT;
}

bool IsRunning() {
    return currentState == GameState::RUNNING;
}

bool CanProcessDirection() {
    return currentState == GameState::RUNNING;
}

void TogglePause() {
    if (currentState == GameState::RUNNING) {
        currentState = GameState::PAUSED;
    }
    else if (currentState == GameState::PAUSED) {
        currentState = GameState::RUNNING;
    }
}