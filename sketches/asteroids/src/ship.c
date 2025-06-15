#include "ship.h"
#include <math.h>
#include <raylib.h>
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
  shipPointer->velocity.x = 1;
  shipPointer->velocity.y = 0;

  shipPointer->isBoosting = false;
  shipPointer->color = WHITE;
  shipPointer->rotation = SHIP_ROTATION_SPEED;
  shipPointer->sides = 3;
  shipPointer->radius = 40;

  return shipPointer;
}

void rotateShip(Ship *ship, int direction) {

  if (direction == KEY_RIGHT) {
    ship->rotation += SHIP_ROTATION_SPEED;
  } else if (direction == KEY_LEFT) {
    ship->rotation -= SHIP_ROTATION_SPEED;
  }
}
