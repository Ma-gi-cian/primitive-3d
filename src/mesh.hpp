#ifndef MESH_H
#define MESH_H

#include "Triangle/Triangle.hpp"
#include "types.h"
#define N_MESH_VERTICES 8
#define N_MESH_FACES (6 * 2)

extern vec3 mesh_vertices[N_MESH_VERTICES];
extern face_t mesh_faces[N_MESH_FACES];

#endif
