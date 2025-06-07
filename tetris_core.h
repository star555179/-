#pragma once
#include <vector>
#include <array>
#include<windows.h>
// 俄罗斯方块7种形状
enum BlockType { I, O, S, Z, L, J, T };

// 颜色定义
const int BLOCK_COLORS[7] = {
    RGB(0, 255, 255), RGB(255, 255, 0), RGB(0, 255, 0), RGB(255,0,0),
    RGB(255,127,39), RGB(0,0,255), RGB(255,0,255)
};

// 旋转后的方块形状数据
// 替换 BLOCK_SHAPES 的声明为：
extern const std::array<std::array<std::array<std::array<int, 4>, 4>, 4>, 7> BLOCK_SHAPES;

// 继承与多态
class Block {
protected:
    int x, y;  // 左上角坐标（格子）
    int rotation; // 当前旋转状态
    BlockType type;
public:
    Block(BlockType t);
    virtual ~Block() {}
    virtual void rotate();
    virtual void move(int dx, int dy);
    void getShape(std::array<std::array<int, 4>, 4>& shape) const;
    int getX() const { return x; }
    int getY() const { return y; }
    BlockType getType() const { return type; }
    int getRotation() const { return rotation; }
    void setPos(int nx, int ny) { x = nx; y = ny; }
    void setRotation(int rot) { rotation = rot; }
};

class IBlock : public Block {
public:
    IBlock() : Block(I) {}
    void rotate() override; // 直线形的特殊旋转
};

// 地图20行10列
class Map {
private:
    int grid[20][10]{};
public:
    bool check(const Block& block) const;
    void place(const Block& block);
    int clearLines(); // 消行
    bool isFull() const;
    int getCell(int r, int c) const { return grid[r][c]; }
    void reset();
};