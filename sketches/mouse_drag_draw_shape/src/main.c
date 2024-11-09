#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // ===== INITIALIZATION =====
  const int screenWidth = 1000;
  const int screenHeight = 900;

  Vector2 circlePosition = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  Color circleColor = DARKBLUE;

  SetTargetFPS(60);
  InitWindow(screenWidth, screenHeight, "Mouse Drag Draw Shape");

  // Create a RenderTexture2D to use as a canvas - target for offscreen
  // rendering (aka frame buffer)
  // target holds the result of rendering operations not directly drawn to
  // screen to improve performance useful effects like post-processing or
  // rendering parts of a scene that don't change often

  // target can be drawn as a single texture which can be more performant and
  // allows for more advanced effects. other functions can draw to the target
  // instead of the screen
  RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

  // Clear render texture before entering the game loop
  BeginTextureMode(target);
  ClearBackground(RAYWHITE);
  EndTextureMode();

  // ===== MAIN GAME LOOP =====
  while (!WindowShouldClose()) {

    Vector2 mousePosition = GetMousePosition();

    BeginTextureMode(target);
    DrawCircleV(mousePosition, 10, circleColor); // draw to frame buffer
    EndTextureMode();

    BeginDrawing();

    ClearBackground(RAYWHITE);

    // draw target texture containing previous draw results
    Rectangle rectangle = {0, 0, target.texture.width, -target.texture.height};
    Vector2 position = {0, 0};
    DrawTextureRec(target.texture, rectangle, position, WHITE);

    EndDrawing();
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}