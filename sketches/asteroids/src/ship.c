#include "ship.h"
#include "asteroids.h"
#include "utils.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const float SHIP_SIZE = 40;
const float SHIP_ROTATION_SPEED = 2.0F;

// Ship initialization constants
const int SHIP_SIDES = 3;
const float SHIP_RADIUS = 20.0F;
const float INITIAL_HEADING = 0.0F;

// Ship movement constants
const float THRUST_POWER = 2.0F;
const Vector2 THRUST_BASE_DIRECTION = {0, -1};

Ship *initializeShip(Vector2 position) {
  Ship *shipPointer = malloc(sizeof(Ship));
  if (shipPointer == NULL) {
    printf("Memory allocation for ship failed\n");
    return NULL;
  }
  // init position
  shipPointer->position.x = position.x;
  shipPointer->position.y = position.y;
  // init velocity
  shipPointer->velocity.x = 0;
  shipPointer->velocity.y = 0;
  shipPointer->isBoosting = false;
  shipPointer->color = WHITE;
  shipPointer->rotation = SHIP_ROTATION_SPEED;
  shipPointer->sides = SHIP_SIDES;
  shipPointer->radius = SHIP_RADIUS;
  shipPointer->heading = INITIAL_HEADING;

  return shipPointer;
}

void rotateShip(Ship *ship, int direction) {

  if (direction == KEY_RIGHT) {
    ship->heading += ship->rotation;
  } else if (direction == KEY_LEFT) {
    ship->heading -= ship->rotation;
  }
}

void boostShip(Ship *ship) {
  Vector2 thrustDirection =
      Vector2Rotate(THRUST_BASE_DIRECTION, ship->heading * DEG2RAD);
  Vector2 boost = Vector2Scale(thrustDirection, THRUST_POWER * GetFrameTime());

  ship->velocity = Vector2Add(ship->velocity, boost);
}

void wrapShip(Ship *ship, int screenWidth, int screenHeight) {
  wrapAroundScreen(&ship->position, ship->radius, screenWidth, screenHeight);
}

bool checkShipAsteroidCollision(Ship *ship, Asteroid *asteroids,
                                int asteroidCount) {
  for (int i = 0; i < asteroidCount; i++) {
    if (asteroids[i].radius > 0) {
      float distance = Vector2Distance(ship->position, asteroids[i].position);
      float collisionDistance = ship->radius + asteroids[i].radius;

      if (distance < collisionDistance) {
        printf("COLLISION DETECTED! Ship hit asteroid %d\n", i);
        return true;
      }
    }
  }
  return false;
}
