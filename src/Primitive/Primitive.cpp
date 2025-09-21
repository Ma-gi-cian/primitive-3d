#include "Primitive.hpp"
#include <algorithm> 

void Primitive::setTarget(uint32_t* buffer, int width, int height) {
    target_buffer = buffer;
    buffer_width = width;
    buffer_height = height;
}

void Primitive::drawSquare(int rect_x, int rect_y, int rect_width, int rect_height, uint32_t color) {
    if (!target_buffer) return;

    int start_x = std::max(0, rect_x);
    int start_y = std::max(0, rect_y);
    int end_x = std::min(buffer_width, rect_x + rect_width);
    int end_y = std::min(buffer_height, rect_y + rect_height);

    for (int y = start_y; y < end_y; y++) {
        for (int x = start_x; x < end_x; x++) {
            target_buffer[(buffer_width * y) + x] = color;
        }
    }
}

void Primitive::drawPixel(int posx, int posy, uint32_t color){
    if (posx, posy >= 0 && posx < buffer_width && posy < buffer_height) {
        target_buffer[(buffer_width * posy) + posx] = color;
    }
}