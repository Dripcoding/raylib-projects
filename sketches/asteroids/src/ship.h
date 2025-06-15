#ifndef SHIP_H
#define SHIP_H

#include "raylib.h"

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
} Ship;

Ship* initializeShip(Vector2 position);

void rotateShip(Ship* ship, int direction);

#endif // SHIP_H
