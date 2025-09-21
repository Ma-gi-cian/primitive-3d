#include "Stage.hpp"
#include <iostream>
#include <SDL2/SDL.h>

Stage::Stage() {
    is_running = initialize();
    if (!is_running) {
        std::cerr << "Stage initialization failed." << std::endl;
    }
}

Stage::~Stage() {
    cleanup();
}

void Stage::play() {
    while (is_running) {
        processInput();
        update();
        render();
    }
}


bool Stage::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initialize sld: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    window_width = displayMode.w;
    window_height = displayMode.h;

    window = SDL_CreateWindow(
        "Software Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
    if (!texture) {
        std::cerr << "Failed to create SDL texture: " << SDL_GetError() << std::endl;
        return false;
    }

    color_buffer = std::make_unique<uint32_t[]>(window_width * window_height);
    if (!color_buffer) {
        std::cerr << "Failed to allocate color buffer." << std::endl;
        return false;
    }

    return true;
}

void Stage::cleanup() {
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}


void Stage::processInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    is_running = false;
                }
                break;
        }
    }
}

void Stage::update() {
    clearColorBuffer(0xFFFFFFFF);
}

void Stage::render() {
    SDL_UpdateTexture(texture, NULL, color_buffer.get(), window_width * sizeof(uint32_t));

    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_RenderPresent(renderer);
}

// I need a primitive class for this, maybe a primitive class and then also a 
void Stage::drawSquare(int posx, int posy, int width , int height, uint32_t color) {
    // Boundary error and core dump because it is writing outside of the expected space.

    // check if it is not negative or something - so that it does not behave unexpectedly if negative values are given
    int beginx = std::max(0, posx);
    int beginy = std::max(0, posy);

    int endx = std::min(window_width, beginx + width);
    int endy = std::min(window_height, beginy + height);
    for(int y = beginy; y < endy; y++){
        for(int x = beginx; x < endx ; x++){
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void Stage::clearColorBuffer(uint32_t color) {
    if (!color_buffer) return;
    
    std::fill(color_buffer.get(), color_buffer.get() + (window_width * window_height), color);

    drawSquare(500, 500, 1400, 1400, 0x00000000);

}
