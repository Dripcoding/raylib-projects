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
  shipPointer->sides = 3;
  shipPointer->radius = 20;
  shipPointer->heading = 0;

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
  float thrustPower = 2.0F;

  Vector2 direction = {0, -1};
  Vector2 thrustDirection = Vector2Rotate(direction, ship->heading * DEG2RAD);
  Vector2 boost = Vector2Scale(thrustDirection, thrustPower * GetFrameTime());

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
