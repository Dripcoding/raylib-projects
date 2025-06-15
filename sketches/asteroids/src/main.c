#include "raylib.h"
#include "ship.h"
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(void) {
  // ===== INITIALIZATION START =====
  SetTargetFPS(60);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");
  Ship *ship = initializeShip(
      (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2});
  if (ship == NULL) {
    printf("Failed to initialize ship\n");
    CloseWindow();
    return -1;
  }

  // ===== INITIALIZATION END =====

  // ===== GAME LOOP START =====
  while (!WindowShouldClose()) {

    // ===== UPDATE SHIP START =====
    if (ship->isBoosting) {
      boostShip(ship);
    }

    wrapShip(ship, SCREEN_WIDTH, SCREEN_HEIGHT);

    ship->position = Vector2Add(ship->position, ship->velocity);

    if (IsKeyDown(KEY_RIGHT)) {
      rotateShip(ship, KEY_RIGHT);
    } else if (IsKeyDown(KEY_LEFT)) {
      rotateShip(ship, KEY_LEFT);
    } else if (IsKeyDown(KEY_UP)) {
      ship->isBoosting = true;
    } else if (IsKeyReleased(KEY_UP)) {
      ship->isBoosting = false;
    }
    // ===== UPDATE SHIP END =====

    // ===== DRAWING START =====
    BeginDrawing();
    ClearBackground(BLACK);
    DrawPolyLines(ship->position, 3, ship->radius, ship->heading, ship->color);

    EndDrawing();
    // ===== DRAWING END =====
  }
  // ===== GAME LOOP END =====

  // Clean up memory
  free(ship);
  CloseWindow();
  return 0;
}
