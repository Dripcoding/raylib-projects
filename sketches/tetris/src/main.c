#include "grid.h"
#include "raylib.h"

const int SCREEN_WIDTH = 350;
const int SCREEN_HEIGHT = 650;

int main(void) {
  // ===== INITIALIZATION START =====

  SetTargetFPS(60);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");

  grid *gridPointer = initializeGrid();

  // ====== INITIALIZATION END =====

  while (!WindowShouldClose()) {
    // ===== UPDATE START =====

    // ====== UPDATE END =====

    // ===== DRAW START =====

    BeginDrawing();

    ClearBackground(BLACK);

    drawGrid(gridPointer);

    EndDrawing();
    // ====== DRAW END =====
  }

  CloseWindow();
  return 0;
}
