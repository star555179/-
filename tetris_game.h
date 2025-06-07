#pragma once
#include "tetris_core.h"
#include <memory>
#include <random>

class TetrisGame {
private:
    Map map;
    std::unique_ptr<Block> curBlock;
    std::unique_ptr<Block> nextBlock;
    int score;
    int lines;
    bool paused;
    bool over;
    int speed;
    std::mt19937 rng;
    // 工厂方法，体现面向对象
    std::unique_ptr<Block> createRandomBlock();
public:
    TetrisGame();
    void start();
    void tick();
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotate();
    void drop();
    void togglePause();
    void restart();
    // 获取器
    const Map& getMap() const { return map; }
    const Block* getCurBlock() const { return curBlock.get(); }
    const Block* getNextBlock() const { return nextBlock.get(); }
    int getScore() const { return score; }
    int getLines() const { return lines; }
    bool isPaused() const { return paused; }
    bool isOver() const { return over; }
    int getSpeed() const { return speed; }
};