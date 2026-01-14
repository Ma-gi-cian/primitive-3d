#include "Primitive.hpp"
#include <algorithm>
#include <cmath>

/*
 * This file mainly deals with points and their transformation.
 */

void Primitive::setTarget(uint32_t *buffer, int width, int height) {
  target_buffer = buffer;
  buffer_width = width;
  buffer_height = height;
}

ivec3 camera_position = {.x = 0, .y = 0, .z = -5};
float fov = 640;

vec3 Primitive::vec3_rotate_x(vec3 vertices, float angle) {
  vec3 rotated_vector = {
      .x = vertices.x,
      .y = vertices.y * std::cos(angle) - vertices.z * std::sin(angle),
      .z = vertices.y * std::sin(angle) + vertices.z * std::cos(angle)};
  return rotated_vector;
}

vec3 Primitive::vec3_rotate_y(vec3 vertices, float angle) {
  vec3 rotated_vector = {
      .x = vertices.x * std::cos(angle) - vertices.z * std::sin(angle),
      .y = vertices.y,
      .z = vertices.x * std::sin(angle) + vertices.z * std::cos(angle)};
  return rotated_vector;
}

vec3 Primitive::vec3_rotate_z(vec3 vertices, float angle) {
  vec3 rotated_vector = {
      .x = vertices.x * std::cos(angle) - vertices.y * std::sin(angle),
      .y = vertices.x * std::sin(angle) + vertices.y * std::cos(angle),
      .z = vertices.z};
  return rotated_vector;
}

vec2 Primitive::project(vec3 world_point, Camera camera) {
  // 1:First transform from world space to camera space
  // Translate point relative to camera position
  vec3 relative_point = {
      .x = world_point.x - camera.position.x,
      .y = world_point.y - camera.position.y,
      .z = world_point.z - camera.position.z
  };

  // 2: apply camera rotation (inverse rotations in reverse order)
  // Camera rotation means we rotate the world in the OPPOSITE direction
  vec3 rotated_z = vec3_rotate_z(relative_point, -camera.rotation.z);
  vec3 rotated_y = vec3_rotate_y(rotated_z, -camera.rotation.y);
  vec3 rotated_x = vec3_rotate_x(rotated_y, -camera.rotation.x);

  // 3: Perspective projection
  // Prevent division by zero or negative Z
  if (rotated_x.z <= 0.1f) {
    return {.x = -1, .y = -1}; // Return invalid point (clip it later)
  }

  vec2 projected_point = {
      .x = (rotated_x.x * camera.fov) / rotated_x.z +
           static_cast<float>(buffer_width) / 2.0f,
      .y = (rotated_x.y * camera.fov) / rotated_x.z +
           static_cast<float>(buffer_height) / 2.0f
  };

  return projected_point;
}

vec2 Primitive::project(vec3 points, Camera camera) {
  vec3 rotation = camera.rotation;
  vec3 rotated_points_x = vec3_rotate_x(points, rotation.x);
  vec3 rotated_points_y = vec3_rotate_y(rotated_points_x, rotation.y);
  vec3 rotated_points = vec3_rotate_z(rotated_points_y, rotation.z);
  rotated_points.z -= camera.position.z;
  vec2 projected_point = {
      .x = (rotated_points.x * camera.fov) / rotated_points.z +
           static_cast<float>(buffer_width) / 2.0f,
      .y = (rotated_points.y * camera.fov) / rotated_points.z +
           static_cast<float>(buffer_height) / 2.0f};
  return projected_point;
}

ivec2 Primitive::project(ivec3 points, Camera camera) {
  ivec2 projected_points = {.x = points.x, .y = points.y};
  return projected_points;
}

void Primitive::drawSquare(int rect_x, int rect_y, int rect_width,
                           int rect_height, uint32_t color) {
  if (!target_buffer)
    return;

  int start_x = std::max(0, rect_x);
  int start_y = std::max(0, rect_y);
  int end_x = std::min(buffer_width, rect_x + rect_width);
  int end_y = std::min(buffer_height, rect_y + rect_height);

  for (int y = start_y; y < end_y; y++) {
    for (int x = start_x; x < end_x; x++) {
      drawPixel(x, y, color);
    }
  }
}

void Primitive::drawPixel(int posx, int posy, uint32_t color) {
  if (posx >= 0 && posy >= 0 && posx < buffer_width && posy < buffer_height) {
    target_buffer[(buffer_width * posy) + posx] = color;
  }
}

void Primitive::drawPixel(ivec3 point, uint32_t color, Camera camera) {
  ivec2 points = project(point, camera);
  if (points.x >= 0 && points.y >= 0 && points.x < buffer_width &&
      points.y < buffer_height) {
    target_buffer[(buffer_width * points.y) + points.x] = color;
  }
}

void Primitive::drawPixel(vec3 point, uint32_t color, Camera camera) {
  vec2 points = project(point, camera);

  if (points.x < 0 || points.y < 0){
    return;
  }
  if (points.x >= 0 && points.y >= 0 && points.x < buffer_width &&
      points.y < buffer_height) {
    target_buffer[(buffer_width * static_cast<int>(points.y)) +
                  static_cast<int>(points.x)] = color;
  }
}

void Primitive::drawRectPixels(int pos_x, int pos_y, int rect_width,
                               int rect_height, int stride, uint32_t color) {
  if (!target_buffer)
    return;

  int start_x = std::max(0, pos_x);
  int start_y = std::max(0, pos_y);

  int end_x = std::min(buffer_width, pos_x + rect_width);
  int end_y = std::min(buffer_height, pos_y + rect_height);
}

void Primitive::drawLine(vec3 point1, vec3 point2, uint32_t color, Camera camera){

}

// void Primitive::drawBitMap(int startx, int starty){
//     for(int y=0; y < 128; y++){
//         for(int x = 0; x < 128 ; x++){
//             uint32_t color = bitmap[y * 128 + x];
//             drawPixel(startx+x, starty+y, color);
//         }
//     }
// }
