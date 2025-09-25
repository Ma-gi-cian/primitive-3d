#pragma once
#include <cstdint>
#include "../types.h"

class Primitive {
public:
    void setTarget(uint32_t* buffer, int width, int height);

    void drawSquare(int rect_x, int rect_y, int rect_width, int rect_height, uint32_t color);

    void drawPixel(int posx, int posy, uint32_t color);
    void drawPixel(ivec3 point, uint32_t color, Camera camera);
    void drawPixel(vec3 point, uint32_t color, Camera camera);

    void drawRectPixels(int posx, int posy, int rect_width, int rect_height, int stride, uint32_t color);

    vec2 project(vec3 points, Camera camera);
    ivec2 project(ivec3 points, Camera camera);

    // void drawBitMap(int startx, int starty);
    
    static const uint32_t bitmap[128 * 128];
 
private:
    uint32_t* target_buffer = nullptr;
    int buffer_width = 0;
    int buffer_height = 0;
};