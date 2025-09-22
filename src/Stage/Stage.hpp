#pragma once 

#include "../types.h"
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
    
    static constexpr int num_points = 9 * 9 * 9;
    vec3 cube_points[num_points];

    bool is_running = false;
    int window_width = 800;
    int window_height = 800;

    void clearColorBuffer(uint32_t color);

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    std::unique_ptr<uint32_t[]> color_buffer;

    Primitive primitives;

    typedef struct {
        vec3 position;
        vec3 rotation;
        float fov_angle;
    } camera;
};
