#ifndef ASTEROIDS_h
#define ASTEROIDS_h

#include "raylib.h"

#define MAX_ASTEROID_COUNT 30
#define MIN_ASTEROID_SPEED 20
#define MAX_ASTEROID_SPEED 80
#define MIN_ASTEROID_ANGLE 0
#define MAX_ASTEROID_ANGLE 360
#define MAX_ASTEROID_VERTICES 10

typedef struct Asteroid {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    Vector2 vertices[MAX_ASTEROID_VERTICES];
    int vertexCount;
    float rotation;
    float rotationSpeed;
} Asteroid;

Asteroid* initializeAsteroids(int screenWidth, int screenHeight);

void generateAsteroidShape(Asteroid* asteroid);

void updateAsteroids(Asteroid* asteroids, int screenWidth, int screenHeight);

void drawAsteroids(Asteroid* asteroids);

Vector2 calcAsteroidPosition(int screenWidth, int screenHeight);

#endif // ASTEROIDS_H
