#include "tetris_game.h"
#include <ctime>

TetrisGame::TetrisGame() : score(0), lines(0), paused(false), over(false), speed(500), rng((unsigned)time(0)) {
    map.reset();
    curBlock = createRandomBlock();
    nextBlock = createRandomBlock();
}
std::unique_ptr<Block> TetrisGame::createRandomBlock() {
    BlockType t = static_cast<BlockType>(rng() % 7);
    switch (t) {
    case I: return std::make_unique<IBlock>();
    default: return std::make_unique<Block>(t);
    }
}
void TetrisGame::start() {
    map.reset();
    curBlock = createRandomBlock();
    nextBlock = createRandomBlock();
    score = 0;
    lines = 0;
    paused = false;
    over = false;
    speed = 500;
}
void TetrisGame::tick() {
    if (paused || over) return;
    curBlock->move(0, 1);
    if (!map.check(*curBlock)) {
        curBlock->move(0, -1);
        map.place(*curBlock);
        int n = map.clearLines();
        score += n * 100;
        lines += n;
        if (lines >= 10) speed = 300;
        if (lines >= 20) speed = 200;
        curBlock = std::move(nextBlock);
        nextBlock = createRandomBlock();
        curBlock->setPos(3, 0);
        if (!map.check(*curBlock)) { over = true; }
    }
}
void TetrisGame::moveLeft() {
    if (paused || over) return;
    curBlock->move(-1, 0);
    if (!map.check(*curBlock)) curBlock->move(1, 0);
}
void TetrisGame::moveRight() {
    if (paused || over) return;
    curBlock->move(1, 0);
    if (!map.check(*curBlock)) curBlock->move(-1, 0);
}
void TetrisGame::moveDown() {
    if (paused || over) return;
    curBlock->move(0, 1);
    if (!map.check(*curBlock)) curBlock->move(0, -1);
}
void TetrisGame::rotate() {
    if (paused || over) return;
    int oldRot = curBlock->getRotation();
    curBlock->rotate();
    if (!map.check(*curBlock)) curBlock->setRotation(oldRot);
}
void TetrisGame::drop() {
    if (paused || over) return;
    while (map.check(*curBlock)) curBlock->move(0, 1);
    curBlock->move(0, -1);
    map.place(*curBlock);
    int n = map.clearLines();
    score += n * 100;
    lines += n;
    curBlock = std::move(nextBlock);
    nextBlock = createRandomBlock();
    curBlock->setPos(3, 0);
    if (!map.check(*curBlock)) { over = true; }
}
void TetrisGame::togglePause() { if (!over) paused = !paused; }
void TetrisGame::restart() { start(); }