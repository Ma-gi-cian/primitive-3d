#include <SDL2/SDL_pixels.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>


SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;

std::unique_ptr<uint32_t[]> color_buffer_ptr;
uint32_t* color_buffer = nullptr;

bool is_running = false;

int window_width = 800;
int window_height = 800;

bool initialize_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initalize sdl" << std::endl;
        return false;
    }

    // We will get the full size of the availble thing present.
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
        std::cerr << "Initialization of the window failed" << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Failed to initialize the renderer" << std::endl;
        return false;
    }

    std::cout << "Successfully initialized the sdl" << std::endl;
    return true;
}

void setup() {
    color_buffer_ptr = std::make_unique<uint32_t[]>(window_width * window_height);
    color_buffer = color_buffer_ptr.get();

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        window_width,
        window_height
    );
}

void destroy_window() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void process_input() {
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

void update() {
}

// Beautiful dots are drawn using this code.
// void draw_points() {
//     for(int i = 0; i<window_height; i++) {
//         for(int j = 0; j < window_width; j++){
//             if (i % 10 == 0 && j % 10 == 0) {
//                 color_buffer[(window_width * i) + j ] = 0x00000000;
//             }
//         }
//     }
// }

// works
void draw_grid(){
    for(int i = 0; i < window_height; i++) {
        for(int j = 0; j < window_width; j++) {
            if (i % 100 == 0 ||  j % 10 == 0){
                color_buffer[window_width * i + j] = 0x00000000;
            }
        }
    }
}




void clear_color_buffer(uint32_t color) {
    if (!color_buffer) return;
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
        }
    }

    draw_grid();
}

void render_color_buffer() {
    if (!texture || !color_buffer) return;
    SDL_UpdateTexture(texture, NULL, color_buffer, (int)window_width * sizeof(uint32_t));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

int main() {
    is_running = initialize_window();
    
    if (is_running) {
        setup();
    }

    while (is_running) {
        process_input();
        update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        clear_color_buffer(0xFFFFFFFF); 

        render_color_buffer();

        SDL_RenderPresent(renderer);
    }

    destroy_window();
    return 0;
}
