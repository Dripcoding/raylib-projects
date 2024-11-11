#include "raylib.h"
#include "stdio.h"

const Color BACKGROUND_COLOR = {230, 230, 250};
const Color RAIN_COLOR = {138, 43, 226, 255};
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000;
const int RAIN_DROP_COUNT = 600;
const Vector2 RAIN_DROP_VEL = {0, 15};
const int RAIN_DROP_WIDTH = 7;
const int RAIN_DROP_HEIGHT = 50;

typedef struct {
  Vector2 pos;
  Vector2 vel;
  int width;
  int height;
  int depth;
  Color color;
} RainDrop;

int main(void) {
  // ===== INITIALIZATION =====
  SetTargetFPS(60);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Purple Rain");

  RainDrop rainDrops[RAIN_DROP_COUNT];

  // initialize rain drops
  for (int i = 0; i < RAIN_DROP_COUNT; i++) {
    Vector2 position = {GetRandomValue(10, SCREEN_WIDTH - 10),
                        GetRandomValue(0, SCREEN_HEIGHT)};
    RainDrop rainDrop = {
        position, RAIN_DROP_VEL, RAIN_DROP_WIDTH,
        RAIN_DROP_HEIGHT,
        GetRandomValue(0, 20), 
        RAIN_COLOR
    };

    rainDrops[i] = rainDrop;

    // rain drops that are further away from the viewer fall slower and are thinner
    // rain drops that are closer to the viewer fall faster and are thicker
    if (rainDrops[i].depth > 0 && rainDrops[i].depth <= 10) {
      rainDrops[i].vel.y = GetRandomValue(3, 5);
      rainDrops[i].width = GetRandomValue(1, 3);
      rainDrops[i].height = GetRandomValue(10, 30);
      rainDrops[i].color = MAROON;
    }
    else {
      rainDrops[i].vel.y = GetRandomValue(10, 20);
      rainDrops[i].width = GetRandomValue(5, 7);
      rainDrops[i].height = GetRandomValue(50, 75);
    }
  }

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
    // ===== UPDATE =====
    for (int i = 0; i < RAIN_DROP_COUNT; i++) {
      // reset rain drop y position once it reaches the bottom of the screen
      if (rainDrops[i].pos.y >= SCREEN_HEIGHT) {
        rainDrops[i].pos.x = GetRandomValue(10, SCREEN_WIDTH - 10);
        rainDrops[i].pos.y = GetRandomValue(0, SCREEN_HEIGHT / 4);
      }

      rainDrops[i].vel.y += 0.002;

      rainDrops[i].pos.y += rainDrops[i].vel.y;
    }

    // ===== BEGIN DRAWING =====
    BeginDrawing();

    ClearBackground(BACKGROUND_COLOR);

    for (int i = 0; i < RAIN_DROP_COUNT; i++) {
      int x = rainDrops[i].pos.x;
      int y = rainDrops[i].pos.y;
      int width = rainDrops[i].width;
      int height = rainDrops[i].height;

      DrawRectangle(x, y, width, height, rainDrops[i].color);
    }

    EndDrawing();
    // ===== END DRAWING =====
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}