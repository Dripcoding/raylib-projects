#include "raylib.h"
#include <complex.h>

const Color BACKGROUND_COLOR = {230, 230, 250, 255};
const Color RAIN_COLOR = {138, 43, 226, 255};
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000;

int main(void) {
  // ===== INITIALIZATION =====
  SetTargetFPS(30);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Purple Rain");

  Vector2 rainDropPos = {400, 50};
  Vector2 rainDropVel = {0, 5};

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
    // ===== UPDATE =====
    rainDropPos.y += rainDropVel.y;

    // ===== BEGIN DRAWING =====
    BeginDrawing();

    ClearBackground(GRAY);

    // define 1 rectangle at the top of the screen
    DrawRectangle(rainDropPos.x, rainDropPos.y, 50, 100, RAIN_COLOR);

    EndDrawing();
    // ===== END DRAWING =====
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}