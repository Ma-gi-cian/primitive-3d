#include "Stage.hpp"
#include "../Primitive/Primitive.hpp"
#include "../mesh.hpp"
#include <SDL2/SDL.h>
#include <SDL_video.h>
#include <iostream>
#include <vector>

Stage::Stage() {
  is_running = initialize();
  if (!is_running) {
    std::cerr << "Stage initialization failed." << std::endl;
  }
}

Stage::~Stage() { cleanup(); }

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

  window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, window_width, window_height,
                            SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    std::cerr << "Failed to create SDL renderer: " << SDL_GetError()
              << std::endl;
    return false;
  }

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING, window_width,
                              window_height);
  if (!texture) {
    std::cerr << "Failed to create SDL texture: " << SDL_GetError()
              << std::endl;
    return false;
  }

  color_buffer = std::make_unique<uint32_t[]>(window_width * window_height);
  if (!color_buffer) {
    std::cerr << "Failed to allocate color buffer." << std::endl;
    return false;
  }

  primitives.setTarget(color_buffer.get(), window_width, window_height);

  camera.fov = 320;
  camera.position = vec3({0, 0, 5});
  camera.rotation = vec3({0, 0, 0});

  return true;
}

void Stage::cleanup() {
  if (texture)
    SDL_DestroyTexture(texture);
  if (renderer)
    SDL_DestroyRenderer(renderer);
  if (window)
    SDL_DestroyWindow(window);
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
  clearColorBuffer(0xFF000000);

  camera.rotation.x += 0.01;
  camera.rotation.y += 0.01;
  camera.rotation.z += 0.01;

  for (int i = 0; i < N_MESH_FACES; i++) {
    face_t mesh_face = mesh_faces[i];

    vec3 face_vertices[3];
    face_vertices[0] = mesh_vertices[mesh_face.a - 1];
    face_vertices[1] = mesh_vertices[mesh_face.b - 1];
    face_vertices[2] = mesh_vertices[mesh_face.c - 1];

    for (int j = 0; j < 3; j++) {
      primitives.drawPixel(face_vertices[j], 0xFFFFFFFF, camera);
    }
  }

  primitives.drawSquare(40, 40, 300, 500, 0xFFFF0000);
}

  /*
  std::vector<vec3> indices;
  for(float x = -1.0; x <= 1.0; x+=0.25) {
      for(float y = -1.0; y <= 1.0 ; y+=0.25 ){
          for(float z = -1.0; z < 1.0; z+=0.25){
              vec3 point = {.x = x, .y = y, .z=z};
              indices.push_back(point);
          }
      }
  }

  //


  for(int i = 0; i < indices.size(); i++){
      primitives.drawPixel(indices[i], 0xFF000000, camera);
  }

   */

void Stage::render() {
  SDL_UpdateTexture(texture, NULL, color_buffer.get(),
                    window_width * sizeof(uint32_t));

  SDL_RenderCopy(renderer, texture, NULL, NULL);

  SDL_RenderPresent(renderer);
}

void Stage::clearColorBuffer(uint32_t color) {
  if (!color_buffer)
    return;

  std::fill(color_buffer.get(),
            color_buffer.get() + (window_width * window_height), color);
}
