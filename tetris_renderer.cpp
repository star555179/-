#include "tetris_renderer.h"
#include <graphics.h>
#include <string>

// ���Ƶ�������
static void drawCell(int x, int y, int color) {
    setfillcolor(color);
    solidrectangle(x, y, x + 24, y + 24);
    setlinecolor(RGB(60, 60, 60));
    rectangle(x, y, x + 24, y + 24);
}

void TetrisRenderer::draw(const TetrisGame& game) {
    // ����
    setbkcolor(RGB(30, 30, 30));
    cleardevice();

    // ���Ƶ�ͼ
    const Map& map = game.getMap();
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 10; ++j) {
            int v = map.getCell(i, j);
            int color = v ? BLOCK_COLORS[v - 1] : RGB(60, 60, 60);
            drawCell(j * 24 + 30, i * 24 + 30, color);
        }

    // ���Ƶ�ǰ����
    if (const Block* blk = game.getCurBlock()) {
        std::array<std::array<int, 4>, 4> shape;
        blk->getShape(shape);
        int x = blk->getX(), y = blk->getY(), t = blk->getType();
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (shape[i][j])
                    drawCell((x + j) * 24 + 30, (y + i) * 24 + 30, BLOCK_COLORS[t]);
    }

    // ������һ������
    outtextxy(280, 30, L"��һ����");
    if (const Block* nb = game.getNextBlock()) {
        std::array<std::array<int, 4>, 4> shape;
        nb->getShape(shape);
        int t = nb->getType();
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (shape[i][j])
                    drawCell(280 + j * 24, 60 + i * 24, BLOCK_COLORS[t]);
    }

    // ������״̬
    setbkmode(TRANSPARENT);
    std::wstring s = L"����: " + std::to_wstring(game.getScore());
    outtextxy(280, 180, s.c_str());
    std::wstring l = L"����: " + std::to_wstring(game.getLines());
    outtextxy(280, 210, l.c_str());
    if (game.isPaused()) outtextxy(120, 230, L"����ͣ����P�ָ�");
    if (game.isOver()) outtextxy(80, 230, L"��Ϸ��������R�ؿ�");

    // ������ʾ
    settextcolor(RGB(160, 160, 160));
    outtextxy(250, 300, L"������");
    outtextxy(250, 320, L"W��/�ϼ�ͷ����ת");
    outtextxy(250, 340, L"A��/���ͷ������");
    outtextxy(250, 360, L"D��/�Ҽ�ͷ������");
    outtextxy(250, 380, L"S��/�¼�ͷ������");
    outtextxy(250, 400, L"�ո�/�س�������");
    outtextxy(250, 420, L"P����ͣ  R���ؿ�  ESC���˳�");
}

void TetrisRenderer::drawGameOver(const TetrisGame& game) {
    draw(game);
    settextcolor(RGB(255, 0, 0));
    setbkmode(TRANSPARENT);
    outtextxy(80, 150, L"��Ϸ��������������˳�");
}