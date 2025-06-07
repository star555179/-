#include "tetris_core.h"

// 7种方块的所有旋转形状（4*4） 
// 正确嵌套：每个方块类型只有一层大括号
#include "tetris_core.h"

const std::array<std::array<std::array<std::array<int, 4>, 4>, 4>, 7> BLOCK_SHAPES = { {
        // I型
        {{
            {{ {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} }},
            {{ {0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0} }},
            {{ {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} }},
            {{ {0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0} }}
        }},
    // O型
    {{
        {{ {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} }}
    }},
    // S型
    {{
        {{ {0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,0,0}, {0,1,1,0}, {0,0,1,0}, {0,0,0,0} }},
        {{ {0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,0,0}, {0,1,1,0}, {0,0,1,0}, {0,0,0,0} }}
    }},
    // Z型
    {{
        {{ {1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,0,1,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0} }},
        {{ {1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,0,1,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0} }}
    }},
    // L型
    {{
        {{ {0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,0,0}, {0,1,0,0}, {0,1,1,0}, {0,0,0,0} }},
        {{ {1,1,1,0}, {1,0,0,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {1,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0} }}
    }},
    // J型
    {{
        {{ {1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,1,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0} }},
        {{ {1,1,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0} }}
    }},
    // T型
    {{
        {{ {0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,0,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0} }},
        {{ {1,1,1,0}, {0,1,0,0}, {0,0,0,0}, {0,0,0,0} }},
        {{ {0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0} }}
    }}
} };
Block::Block(BlockType t) : x(3), y(0), rotation(0), type(t) {}

void Block::rotate() {
    rotation = (rotation + 1) % 4;
}

void Block::move(int dx, int dy) {
    x += dx; y += dy;
}

void Block::getShape(std::array<std::array<int, 4>, 4>& shape) const {
    shape = BLOCK_SHAPES[type][rotation];
}

void IBlock::rotate() {
    // I方块只有两种旋转
    rotation = (rotation + 1) % 2;
}

bool Map::check(const Block& block) const {
    std::array<std::array<int, 4>, 4> shape;
    block.getShape(shape);
    int x = block.getX(), y = block.getY();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (shape[i][j]) {
                int xi = x + j, yi = y + i;
                if (xi < 0 || xi >= 10 || yi < 0 || yi >= 20) return false;
                if (grid[yi][xi]) return false;
            }
    return true;
}

void Map::place(const Block& block) {
    std::array<std::array<int, 4>, 4> shape;
    block.getShape(shape);
    int x = block.getX(), y = block.getY(), type = block.getType();
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (shape[i][j]) {
                int xi = x + j, yi = y + i;
                if (xi >= 0 && xi < 10 && yi >= 0 && yi < 20)
                    grid[yi][xi] = type + 1;
            }
}

int Map::clearLines() {
    int lines = 0;
    for (int i = 19; i >= 0; --i) {
        bool full = true;
        for (int j = 0; j < 10; ++j)
            if (grid[i][j] == 0) full = false;
        if (full) {
            ++lines;
            for (int k = i; k > 0; --k)
                for (int j = 0; j < 10; ++j)
                    grid[k][j] = grid[k - 1][j];
            for (int j = 0; j < 10; ++j)
                grid[0][j] = 0;
            ++i; // 重新检查本行
        }
    }
    return lines;
}

bool Map::isFull() const {
    for (int j = 0; j < 10; ++j)
        if (grid[0][j]) return true;
    return false;
}

void Map::reset() {
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 10; ++j)
            grid[i][j] = 0;
}