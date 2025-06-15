#include "raylib.h"
#include "ship.h"
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
    // ===== UPDATE START =====

    if (IsKeyDown(KEY_RIGHT)) {
      rotateShip(ship, KEY_RIGHT);
    } else if (IsKeyDown(KEY_LEFT)) {
      rotateShip(ship, KEY_LEFT);
    }

    // ===== UPDATE END =====

    // ===== DRAWING START =====
    BeginDrawing();
    ClearBackground(BLACK);
    DrawPolyLines(ship->position, 3, 40, ship->rotation, ship->color);

    EndDrawing();
    // ===== DRAWING END =====
  }
  // ===== GAME LOOP END =====

  // Clean up memory
  free(ship);
  CloseWindow();
  return 0;
}
