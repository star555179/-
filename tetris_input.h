#pragma once
#include "tetris_game.h"

class TetrisInput {
public:
    // 返回false表示要退出
    bool processInput(int key, TetrisGame& game);
};