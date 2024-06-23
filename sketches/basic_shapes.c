#include "raylib.h"
#include <stdlib.h>

int main(void) {
  // ===== INITIALIZATION =====
  const int screenWidth = 1000;
  const int screenHeight = 900;

  SetTargetFPS(60);
  InitWindow(screenWidth, screenHeight, "Basic Shapes");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw point/pixel
    DrawPixel(screenWidth / 2.0f, screenHeight / 2.0f, RED);

    // draw line
    DrawLine(100, 100, 200, 100, MAROON);

    // draw circle
    DrawCircle(500, 500, 20.0f, DARKBLUE);

    Vector2 circleCenter = {500, 600};
    DrawCircleSector(circleCenter, 20.0f, 0.0, -90.0, 100, RED);

    Vector2 circleCenter2 = {500, 650};
    DrawCircleSectorLines(circleCenter2, 20.0f, 0.0, -90.0, 100, RED);

    // draw rectangle
    DrawRectangle(200, 200, 200, 100, DARKBLUE);
    DrawRectangleLines(300, 300, 200, 100, BLACK);

    Rectangle rectangle = {450, 450, 200, 100};
    DrawRectangleRec(rectangle, RED);

    Rectangle rectangle1 = {150, 550, 200, 100};
    DrawRectangleRounded(rectangle1, 0.5, 10, MAROON);

    // draw triangle
    // DrawTriangle((Vector2){600, 200}, (Vector2){550, 300}, (Vector2){650,
    // 300},
    //              VIOLET);
    DrawTriangleLines((Vector2){600, 200}, (Vector2){550, 300},
                      (Vector2){650, 300}, MAROON);

    // draw ring
    DrawRing((Vector2){500, 700}, 10.0f, 20.0f, 0.0, -180.0, 100, GREEN);
    EndDrawing();
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}