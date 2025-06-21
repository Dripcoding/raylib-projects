#ifndef SHIP_H
#define SHIP_H

#include "raylib.h"
#include "asteroids.h"

typedef struct Ship {
    Vector2 position;
    Vector2 velocity;
    Vector2 vertexOne;
    Vector2 vertexTwo;
    Vector2 vertexThree;
    bool isBoosting;
    Color color;
    float rotation;
    int sides;
    float radius;
    float heading;
} Ship;

Ship* initializeShip(Vector2 position);

void rotateShip(Ship* ship, int direction);

void boostShip(Ship* ship);

void drawShip(Ship* ship);

void wrapShip(Ship* ship, int screenWidth, int screenHeight);

bool checkShipAsteroidCollision(Ship* ship, Asteroid* asteroids, int asteroidCount);

#endif // SHIP_H
