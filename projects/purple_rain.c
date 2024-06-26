#include "raylib.h"
#include <complex.h>

const Color BACKGROUND_COLOR = {230, 230, 250, 255};
const Color RAIN_COLOR = {138, 43, 226, 255};
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000;
const Vector2 RAIN_DROP_VEL = {0, 5};
const int RAIN_DROP_WIDTH = 15;
const int RAIN_DROP_HEIGHT = 50;

typedef struct {
  Vector2 pos;
  Vector2 vel;
  int width;
  int height;
} RainDrop;

int main(void) {
  // ===== INITIALIZATION =====
  SetTargetFPS(30);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Purple Rain");

  RainDrop rainDrops[100];

  for (int i = 0; i < 100; i++) {
    Vector2 position = {GetRandomValue(10, SCREEN_WIDTH - 10),
                        GetRandomValue(10, SCREEN_HEIGHT / 10)};
    rainDrops[i].pos = position;
    rainDrops[i].vel = RAIN_DROP_VEL;
    rainDrops[i].width = RAIN_DROP_WIDTH;
    rainDrops[i].height = RAIN_DROP_HEIGHT;
  }

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
    // ===== UPDATE =====
    for (int i = 0; i < 100; i++) {
      rainDrops[i].pos.y += RAIN_DROP_VEL.y;
    }

    // ===== BEGIN DRAWING =====
    BeginDrawing();

    ClearBackground(GRAY);

    for (int i = 0; i < 100; i++) {
      int x = rainDrops[i].pos.x;
      int y = rainDrops[i].pos.y;
      int width = rainDrops[i].width;
      int height = rainDrops[i].height;

      DrawRectangle(x, y, width, height, RAIN_COLOR);
    }

    EndDrawing();
    // ===== END DRAWING =====
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}