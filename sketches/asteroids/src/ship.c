#include "ship.h"
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Ship *initializeShip(float x, float y) {
  Ship *shipPointer = malloc(sizeof(Ship));
  if (shipPointer == NULL) {
    printf("Memory allocation for ship failed\n");
    return NULL;
  }
  shipPointer->position.x = x;
  shipPointer->position.y = y;
  shipPointer->velocity.x = 1;
  shipPointer->velocity.y = 0;
  // Create a triangle pointing straight up
  shipPointer->vertexOne.x = x;
  shipPointer->vertexOne.y = y - 30;
  // bottom left vertex
  shipPointer->vertexTwo.x = x - 20;
  shipPointer->vertexTwo.y = y + 20;
  // bottom right vertex
  shipPointer->vertexThree.x = x + 20;
  shipPointer->vertexThree.y = y + 20;

  shipPointer->isBoosting = false;
  shipPointer->color = WHITE;

  return shipPointer;
}
