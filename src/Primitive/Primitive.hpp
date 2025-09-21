#pragma once
#include <cstdint>

class Primitive {
public:
    void setTarget(uint32_t* buffer, int width, int height);

    void drawSquare(int rect_x, int rect_y, int rect_width, int rect_height, uint32_t color);

private:
    uint32_t* target_buffer = nullptr;
    int buffer_width = 0;
    int buffer_height = 0;
};
