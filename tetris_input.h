#pragma once
#include "tetris_game.h"

class TetrisInput {
public:
    // ����false��ʾҪ�˳�
    bool processInput(int key, TetrisGame& game);
};