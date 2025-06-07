#include <graphics.h>
#include <conio.h>
#include <iostream>
#include "tetris_game.h"
#include "tetris_renderer.h"
#include "tetris_input.h"

int main() {
    initgraph(480, 600, SHOWCONSOLE); // SHOWCONSOLE显示控制台，方便调试
    TetrisGame game;
    TetrisRenderer renderer;
    TetrisInput input;

    DWORD lastTick = GetTickCount();
    bool running = true;

    ExMessage msg;
    BeginBatchDraw();
    while (running) {
        // 使用EasyX的消息队列获取按键
        while (peekmessage(&msg)) {
            if (msg.message == WM_KEYDOWN) {
                running = input.processInput(msg.vkcode, game);
            }
        }

        // 自动下落
        DWORD now = GetTickCount();
        if (!game.isPaused() && now - lastTick > game.getSpeed()) {
            game.tick();
            lastTick = now;
        }

        // 渲染
        renderer.draw(game);
        FlushBatchDraw();    // 刷新到屏幕

        Sleep(16);
    }

    EndBatchDraw();
    closegraph();
    return 0;
}