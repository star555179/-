#pragma once
#include <vector>
#include <array>
#include<windows.h>
// ����˹����7����״
enum BlockType { I, O, S, Z, L, J, T };

// ��ɫ����
const int BLOCK_COLORS[7] = {
    RGB(0, 255, 255), RGB(255, 255, 0), RGB(0, 255, 0), RGB(255,0,0),
    RGB(255,127,39), RGB(0,0,255), RGB(255,0,255)
};

// ��ת��ķ�����״����
// �滻 BLOCK_SHAPES ������Ϊ��
extern const std::array<std::array<std::array<std::array<int, 4>, 4>, 4>, 7> BLOCK_SHAPES;

// �̳����̬
class Block {
protected:
    int x, y;  // ���Ͻ����꣨���ӣ�
    int rotation; // ��ǰ��ת״̬
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
    void rotate() override; // ֱ���ε�������ת
};

// ��ͼ20��10��
class Map {
private:
    int grid[20][10]{};
public:
    bool check(const Block& block) const;
    void place(const Block& block);
    int clearLines(); // ����
    bool isFull() const;
    int getCell(int r, int c) const { return grid[r][c]; }
    void reset();
};