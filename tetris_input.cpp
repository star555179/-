#include "tetris_input.h"
#include <windows.h>
#include <stdio.h>
bool TetrisInput::processInput(int key, TetrisGame& game) {
    if (key == VK_ESCAPE) return false;
    if (key == 'P' || key == 'p') game.togglePause();
    if (game.isOver() && (key == 'R' || key == 'r')) game.restart();
    if (game.isPaused() || game.isOver()) return true;

    switch (key) {
    case VK_LEFT:
    case 'A': case 'a':
        game.moveLeft(); break;
    case VK_RIGHT:
    case 'D': case 'd':
        game.moveRight(); break;
    case VK_DOWN:
    case 'S': case 's':
        game.moveDown(); break;
    case VK_UP:
    case 'W': case 'w':
        game.rotate(); break;
    case VK_SPACE:
        game.drop(); break;
    case VK_RETURN:
        game.drop(); break;
    }
    return true;
}