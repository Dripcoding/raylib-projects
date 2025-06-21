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

void drawShip(Ship *ship) {
  // Draw custom triangle aligned with heading
  Vector2 baseDirection = {0, -1}; // Points up
  Vector2 shipDirection = Vector2Rotate(baseDirection, ship->heading * DEG2RAD);

  // Calculate triangle vertices
  Vector2 topVertex =
      Vector2Add(ship->position, Vector2Scale(shipDirection, ship->radius));
  Vector2 leftVertex = Vector2Add(
      ship->position,
      Vector2Rotate((Vector2){-ship->radius * 0.6F, ship->radius * 0.4F},
                    ship->heading * DEG2RAD));
  Vector2 rightVertex = Vector2Add(
      ship->position,
      Vector2Rotate((Vector2){ship->radius * 0.6F, ship->radius * 0.4F},
                    ship->heading * DEG2RAD));

  // Draw triangle outline
  DrawLineV(topVertex, leftVertex, ship->color);
  DrawLineV(leftVertex, rightVertex, ship->color);
  DrawLineV(rightVertex, topVertex, ship->color);

  // DEBUG Draw direction vector for visual reference
  // Vector2 vectorEnd =
  //     Vector2Add(ship->position, Vector2Scale(shipDirection, 50.0F));
  // DrawLineV(ship->position, vectorEnd, GREEN);

  // DEBUG Draw arrowhead for the direction vector
  // Vector2 arrowLeft = Vector2Rotate((Vector2){-5, 10}, ship->heading *
  // DEG2RAD); Vector2 arrowRight = Vector2Rotate((Vector2){5, 10},
  // ship->heading * DEG2RAD); DrawLineV(vectorEnd, Vector2Add(vectorEnd,
  // arrowLeft), GREEN); DrawLineV(vectorEnd, Vector2Add(vectorEnd, arrowRight),
  // GREEN);
}
