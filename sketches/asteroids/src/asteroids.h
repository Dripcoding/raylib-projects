#ifndef ASTEROIDS_h
#define ASTEROIDS_h

#include "raylib.h"

#define MAX_ASTEROID_COUNT 5

typedef struct Asteroid {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
} Asteroid;

Asteroid* initializeAsteroids(int screenWidth, int screenHeight);

void updateAsteroids(Asteroid* asteroids, int screenWidth, int screenHeight);

void drawAsteroids(Asteroid* asteroids);

Vector2 calcAsteroidPosition(int screenWidth, int screenHeight);

#endif // ASTEROIDS_H
