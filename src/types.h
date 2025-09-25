#pragma once

typedef struct {
	float x; 
	float y;
	float z;
} vec3;

typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
	int x;
	int y;
	int z;
} ivec3;

typedef struct {
	int x;
	int y;
} ivec2;

typedef struct {
	vec3 position;
	vec3 rotation;
	float fov;
} Camera;
