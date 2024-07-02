#include "raylib.h"
#include "stdio.h"

const Color BACKGROUND_COLOR = {230, 230, 250, 255};
const Color RAIN_COLOR = {138, 43, 226, 255};
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000;
const int RAIN_DROP_COUNT = 120;
const Vector2 RAIN_DROP_VEL = {0, 5};
const int RAIN_DROP_WIDTH = 7;
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

  RainDrop rainDrops[RAIN_DROP_COUNT];

  for (int i = 0; i < RAIN_DROP_COUNT; i++) {
    Vector2 position = {GetRandomValue(10, SCREEN_WIDTH - 10),
                        GetRandomValue(10, SCREEN_HEIGHT / 10)};
    RainDrop rainDrop = {
        position, RAIN_DROP_VEL, RAIN_DROP_WIDTH,
        GetRandomValue(RAIN_DROP_HEIGHT, RAIN_DROP_HEIGHT * 1.75)};
    rainDrops[i] = rainDrop;
  }

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
    // ===== UPDATE =====
    // todo: impl gravity so drops don't fall at a constant rate

    for (int i = 0; i < RAIN_DROP_COUNT; i++) {
      if (rainDrops[i].pos.y >= SCREEN_HEIGHT) {
        rainDrops[i].pos.y = GetRandomValue(10, SCREEN_HEIGHT / 10);
      }

      rainDrops[i].pos.y += GetRandomValue(RAIN_DROP_VEL.y, 10);
    }

    // ===== BEGIN DRAWING =====
    BeginDrawing();

    ClearBackground(GRAY);

    for (int i = 0; i < RAIN_DROP_COUNT; i++) {
      int x = rainDrops[i].pos.x;
      int y = rainDrops[i].pos.y;
      int width = rainDrops[i].width;
      int height = rainDrops[i].height;

      // todo: add depth to the scene (stroke weight, size of rain drops, etc)

      DrawRectangle(x, y, width, height, RAIN_COLOR);
    }

    EndDrawing();
    // ===== END DRAWING =====
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}