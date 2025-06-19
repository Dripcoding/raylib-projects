#ifndef ASTEROIDS_h
#define ASTEROIDS_h

#include "raylib.h"

#define MAX_ASTEROID_COUNT 30
#define MIN_ASTEROID_SPEED 20
#define MAX_ASTEROID_SPEED 80
#define MIN_ASTEROID_ANGLE 0
#define MAX_ASTEROID_ANGLE 360
#define MAX_ASTEROID_VERTICES 10
#define ASTEROID_SPLIT_THRESHOLD 30.0F

// Asteroid generation constants
#define MIN_ASTEROID_RADIUS 25
#define MAX_ASTEROID_RADIUS 80
#define ASTEROID_SPLIT_SIZE_FACTOR 0.6F
#define MIN_VERTEX_COUNT 6
#define MAX_VERTEX_COUNT 10
#define ANGLE_RANDOMNESS_DEGREES 20
#define DISTANCE_VARIATION_MIN 70.0F
#define DISTANCE_VARIATION_RANGE 80
#define SPLIT_ANGLE_SEPARATION 180.0F
#define ROTATION_SPEED_MIN (-30)
#define ROTATION_SPEED_MAX (30)
#define DEBUG_FONT_SIZE 12

typedef struct Asteroid {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
    Vector2 vertices[MAX_ASTEROID_VERTICES];
    int vertexCount;
    float rotation;
    float rotationSpeed;
    bool hit;
} Asteroid;

Asteroid* initializeAsteroids(int screenWidth, int screenHeight);

void generateAsteroidShape(Asteroid* asteroid);

void updateAsteroids(Asteroid* asteroids, int asteroidCount, int screenWidth, int screenHeight);

void drawAsteroids(Asteroid* asteroids, int asteroidCount);

Asteroid* splitAsteroid(Asteroid* asteroid);

Vector2 calcAsteroidPosition(int screenWidth, int screenHeight);

#endif // ASTEROIDS_H
