#include "raylib.h"
#include "stdio.h"

const Color BACKGROUND_COLOR = {230, 230, 250};
const Color RAIN_COLOR = {138, 43, 226, 255};
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000;
const int RAIN_DROP_COUNT = 500;
const Vector2 RAIN_DROP_VEL = {0, 5};
const int RAIN_DROP_WIDTH = 7;
const int RAIN_DROP_HEIGHT = 50;

typedef struct {
  Vector2 pos;
  Vector2 vel;
  int width;
  int height;
  int depth;
} RainDrop;

int map(int value, int start1, int stop1, int start2, int stop2) {
    return start2 + (value - start1) * (stop2 - start2) / (stop1 - start1);
}

int main(void) {
  // ===== INITIALIZATION =====
  SetTargetFPS(30);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Purple Rain");

  RainDrop rainDrops[RAIN_DROP_COUNT];

  // initialize rain drops
  for (int i = 0; i < RAIN_DROP_COUNT; i++) {
    Vector2 position = {GetRandomValue(10, SCREEN_WIDTH - 10),
                        GetRandomValue(1, SCREEN_HEIGHT)};
    RainDrop rainDrop = {
        position, RAIN_DROP_VEL, RAIN_DROP_WIDTH,
        GetRandomValue(RAIN_DROP_HEIGHT, RAIN_DROP_HEIGHT * 1.75),
        GetRandomValue(0, 20)};
    rainDrops[i] = rainDrop;
  }

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
    Color color = RAIN_COLOR;
    // ===== UPDATE =====
    // todo: impl gravity so drops don't fall at a constant rate

    for (int i = 0; i < RAIN_DROP_COUNT; i++) {
      // reset rain drop y position once it reaches the bottom of the screen
      if (rainDrops[i].pos.y >= SCREEN_HEIGHT) {
        rainDrops[i].pos.y = GetRandomValue(1, SCREEN_HEIGHT / 4);
      }

      rainDrops[i].pos.y += GetRandomValue(RAIN_DROP_VEL.y, 10);
    }

    // ===== BEGIN DRAWING =====
    BeginDrawing();

    ClearBackground(BACKGROUND_COLOR);

    for (int i = 0; i < RAIN_DROP_COUNT; i++) {
      int x = rainDrops[i].pos.x;
      int y = rainDrops[i].pos.y;
      int width = rainDrops[i].width;
      int height = rainDrops[i].height;

      // todo: add depth to the scene (stroke weight, size of rain drops, etc)

      DrawRectangle(x, y, width, height, color);
    }

    EndDrawing();
    // ===== END DRAWING =====
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}