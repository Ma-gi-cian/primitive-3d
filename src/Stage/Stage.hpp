#pragma once 

#include "../Primitive/Primitive.hpp"

#include <memory>
#include <cstdint>


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Stage {
public:
    Stage();

    ~Stage();

    void play();

private:
    bool initialize();    
    void processInput();    
    void update();              
    void render();           
    void cleanup();          

    void drawSquare(int posx, int posy, int width, int height, uint32_t color);

    bool is_running = false;
    int window_width = 800;
    int window_height = 800;

    void clearColorBuffer(uint32_t color);

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    std::unique_ptr<uint32_t[]> color_buffer;

    Primitive primitives;
};
