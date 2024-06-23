#include "raylib.h"
#include <stdlib.h>

int main(void) {
  // ===== INITIALIZATION =====
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Basic Window");

  SetTargetFPS(60);

  // ===== MAIN GAME LOOP =====
  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20,
             LIGHTGRAY);

    EndDrawing();
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}