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
  Ship *ship =
      initializeShip((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2);
  if (ship == NULL) {
    printf("Failed to initialize ship\n");
    CloseWindow();
    return -1;
  }

  // Print ship info once during initialization
  printf("Ship initialized at: %.1f, %.1f\n", ship->position.x,
         ship->position.y);
  printf("Ship vertices: (%.1f,%.1f), (%.1f,%.1f), (%.1f,%.1f)\n",
         ship->vertexOne.x, ship->vertexOne.y, ship->vertexTwo.x,
         ship->vertexTwo.y, ship->vertexThree.x, ship->vertexThree.y);

  // ===== INITIALIZATION END =====

  // ===== GAME LOOP START =====
  while (!WindowShouldClose()) {
    // Update

    // ===== DRAWING START =====
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw the ship triangle
    DrawTriangleLines(ship->vertexOne, ship->vertexTwo, ship->vertexThree,
                      WHITE);

    EndDrawing();
    // ===== DRAWING END =====
  }
  // ===== GAME LOOP END =====

  // Clean up memory
  free(ship);
  CloseWindow();
  return 0;
}
