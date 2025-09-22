#pragma once
#include <cstdint>
#include <vector>

class Primitive {
public:
    void setTarget(uint32_t* buffer, int width, int height);

    void drawSquare(int rect_x, int rect_y, int rect_width, int rect_height, uint32_t color);

    void drawPixel(int posx, int posy, uint32_t color);

    void drawRectPixels(int posx, int posy, int rect_width, int rect_height, int stride, uint32_t color);
 
private:
    uint32_t* target_buffer = nullptr;
    int buffer_width = 0;
    int buffer_height = 0;
    


    // TODO: Decide if we put htis vec2 and vec3 into classes for easy implementation of the functions for it's manipulation
};
