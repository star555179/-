#pragma once
#include "tetris_game.h"

class TetrisRenderer {
public:
    void draw(const TetrisGame& game);
    void drawGameOver(const TetrisGame& game);
};