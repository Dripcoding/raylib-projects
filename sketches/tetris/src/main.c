#include "raylib.h"

const int SCREEN_WIDTH = 0;
const int SCREEN_HEIGHT = 0;

int main() {
  // ===== INITIALIZATION START =====

  SetTargetFPS(60);

  // Create the window and OpenGL context
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");

  // ====== INITIALIZATION END =====

  // game loop
  while (!WindowShouldClose()) {
    // ===== UPDATE START =====

    // ====== UPDATE END =====

    // ===== DRAW START =====

    // drawing
    BeginDrawing();

    // Setup the backbuffer for drawing (clear color and depth buffers)
    ClearBackground(BLACK);

    // draw some text using the default font
    DrawText("Hello Raylib", 200, 200, 20, WHITE);

    EndDrawing();
    // ====== DRAW END =====
  }

  CloseWindow();
  return 0;
}
