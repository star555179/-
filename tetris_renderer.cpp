#include "tetris_renderer.h"
#include <graphics.h>
#include <string>

// 绘制单个格子
static void drawCell(int x, int y, int color) {
    setfillcolor(color);
    solidrectangle(x, y, x + 24, y + 24);
    setlinecolor(RGB(60, 60, 60));
    rectangle(x, y, x + 24, y + 24);
}

void TetrisRenderer::draw(const TetrisGame& game) {
    // 背景
    setbkcolor(RGB(30, 30, 30));
    cleardevice();

    // 绘制地图
    const Map& map = game.getMap();
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 10; ++j) {
            int v = map.getCell(i, j);
            int color = v ? BLOCK_COLORS[v - 1] : RGB(60, 60, 60);
            drawCell(j * 24 + 30, i * 24 + 30, color);
        }

    // 绘制当前方块
    if (const Block* blk = game.getCurBlock()) {
        std::array<std::array<int, 4>, 4> shape;
        blk->getShape(shape);
        int x = blk->getX(), y = blk->getY(), t = blk->getType();
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (shape[i][j])
                    drawCell((x + j) * 24 + 30, (y + i) * 24 + 30, BLOCK_COLORS[t]);
    }

    // 绘制下一个方块
    outtextxy(280, 30, L"下一个：");
    if (const Block* nb = game.getNextBlock()) {
        std::array<std::array<int, 4>, 4> shape;
        nb->getShape(shape);
        int t = nb->getType();
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (shape[i][j])
                    drawCell(280 + j * 24, 60 + i * 24, BLOCK_COLORS[t]);
    }

    // 分数与状态
    setbkmode(TRANSPARENT);
    std::wstring s = L"分数: " + std::to_wstring(game.getScore());
    outtextxy(280, 180, s.c_str());
    std::wstring l = L"行数: " + std::to_wstring(game.getLines());
    outtextxy(280, 210, l.c_str());
    if (game.isPaused()) outtextxy(120, 230, L"【暂停】按P恢复");
    if (game.isOver()) outtextxy(80, 230, L"游戏结束！按R重开");

    // 操作提示
    settextcolor(RGB(160, 160, 160));
    outtextxy(250, 300, L"操作：");
    outtextxy(250, 320, L"W↑/上箭头：旋转");
    outtextxy(250, 340, L"A←/左箭头：左移");
    outtextxy(250, 360, L"D→/右箭头：右移");
    outtextxy(250, 380, L"S↓/下箭头：下移");
    outtextxy(250, 400, L"空格/回车：快落");
    outtextxy(250, 420, L"P：暂停  R：重开  ESC：退出");
}

void TetrisRenderer::drawGameOver(const TetrisGame& game) {
    draw(game);
    settextcolor(RGB(255, 0, 0));
    setbkmode(TRANSPARENT);
    outtextxy(80, 150, L"游戏结束！按任意键退出");
}