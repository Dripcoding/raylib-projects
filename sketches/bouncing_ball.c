#include "raylib.h"
#include <stdlib.h>

int main(void) {
  // ===== INITIALIZATION =====
  const int screenWidth = 800;
  const int screenHeight = 450;

  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetTargetFPS(60);

  InitWindow(screenWidth, screenHeight, "Bouncing Ball");

  Vector2 ballPosition = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  Vector2 ballSpeed = {5.0f, 4.0f};

  int ballRadius = 20;

  bool pause = 0;
  int framesCounter = 0;

  // ===== MAIN GAME LOOP =====
  while (!WindowShouldClose()) {
    // Update
    if (IsKeyPressed(KEY_SPACE)) {
      pause = !pause;
    }

    if (!pause) {
      // update position
      ballPosition.x += ballSpeed.x;
      ballPosition.y -= ballSpeed.y;

      // check collision with walls
      bool hasCollidedWithTopOrBottomWall =
          ballPosition.x >= (GetScreenWidth() - ballRadius) ||
          ballPosition.x <= ballRadius;
      bool hasCollidedWithLeftOrRightWall =
          ballPosition.y >= (GetScreenHeight() - ballRadius) ||
          ballPosition.y <= ballRadius;

      // update speed depending on collisions with walls
      if (hasCollidedWithTopOrBottomWall) {
        ballSpeed.x *= -1;
      }

      if (hasCollidedWithLeftOrRightWall) {
        ballSpeed.y *= -1;
      }
    }

    else
      framesCounter++;

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(ballPosition, ballRadius, MAROON);

    // draw blinking text every half second on pause
    if (pause && (framesCounter / 30) % 2) {
      DrawText("PAUSED", 350, 200, 30, GRAY);
    }

    DrawFPS(10, 10);

    EndDrawing();
  }

  // ===== DE-INITIALIZATION =====
  CloseWindow();

  return 0;
}