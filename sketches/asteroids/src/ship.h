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


} Ship;

Ship* initializeShip(float x, float y);

#endif // SHIP_H
