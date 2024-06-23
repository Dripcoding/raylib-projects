#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "./raygui.h"

int main(void) {
  // ===== INITIALIZATION =====
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetTargetFPS(60);

  InitWindow(screenWidth, screenHeight, "Circle Sector GUI");

  Vector2 center = {(GetScreenWidth() - 300) / 2.0f, GetScreenHeight() / 2.0f};

  float outerRadius = 180.0f;
  float startAngle = 0.0f;
  float endAngle = 180.0f;
  float segments = 10.0f;
  float minSegments = 4;

  // ===== MAIN GAME LOOP =====
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // draw gui section left border
    DrawLine(500, 0, 500, GetScreenHeight(), Fade(LIGHTGRAY, 0.6f));

    // draw gui section
    DrawRectangle(500, 0, GetScreenWidth() - 500, GetScreenHeight(),
                  Fade(LIGHTGRAY, 0.3f));

    // draw circle shape
    DrawCircleSector(center, outerRadius, startAngle, endAngle, (int)segments,
                     Fade(BLUE, 0.3f));

    // draw circle outline
    DrawCircleSectorLines(center, outerRadius, startAngle, endAngle,
                          (int)segments, Fade(BLUE, 0.6f));

    // draw start angle gui control
    Rectangle startAngleRect = {600, 40, 120, 20};
    GuiSliderBar(startAngleRect, "Start Angle", NULL, &startAngle, 0, 720);

    // draw end angle gui control
    Rectangle endAngleRect = {600, 70, 120, 20};
    GuiSliderBar(endAngleRect, "End Angle", NULL, &endAngle, 0, 720);

    // draw radius gui control
    Rectangle radiusRect = {600, 140, 120, 20};
    GuiSliderBar(radiusRect, "Radius", NULL, &outerRadius, 0, 200);

    // draw segments gui control
    Rectangle segmentsRect = {600, 170, 120, 20};
    GuiSliderBar(segmentsRect, "Segments", NULL, &segments, minSegments, 100);

    minSegments = truncf(ceilf((endAngle - startAngle) / 90));

    DrawFPS(10, 10);
    EndDrawing();
  }

  // ===== DEINITIZLIATION =====
  CloseWindow();

  return 0;
}