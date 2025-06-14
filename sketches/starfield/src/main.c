#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float CENTER_X = SCREEN_WIDTH / 2;
const float CENTER_Y = SCREEN_HEIGHT / 2;
const int FPS = 60;
const int STAR_COUNT = 1500;
const float MAX_RADIUS = 16;
const float MIN_RADIUS = 0;
const Color STAR_COLOR = WHITE;

typedef struct Star {
  float x;
  float y;
  float z;
  float prevZ;
} Star;

Star *initializeStars(void) {
  Star *stars = malloc(STAR_COUNT * sizeof(Star));
  if (stars == NULL) {
    return NULL;
  }

  for (int i = 0; i < STAR_COUNT; i++) {
    Star star = {.x = (float)GetRandomValue((int)-CENTER_X, (int)CENTER_X),
                 .y = (float)GetRandomValue((int)-CENTER_Y, (int)CENTER_Y),
                 .z = (float)GetRandomValue(0, SCREEN_WIDTH),
                 .prevZ = (float)GetRandomValue(0, SCREEN_WIDTH)};

    stars[i] = star;
  }

  return stars;
}

int main(void) {
  // ===== INITIALIZATION START =====
  SetTargetFPS(60);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starfield");
  Star *stars = initializeStars();

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
    // ==== UPDATE START ====
    for (int i = 0; i < STAR_COUNT; i++) {
      // use mouse position to control z
      stars[i].z -=
          Remap((float)GetMouseX(), 0.0F, (float)SCREEN_WIDTH, 0.0F, 50.0F);

      if (stars[i].z < 1) {
        stars[i].z = (float)SCREEN_WIDTH;
        stars[i].x = (float)GetRandomValue((int)-CENTER_X, (int)CENTER_X);
        stars[i].y = (float)GetRandomValue((int)-CENTER_Y, (int)CENTER_Y);
        stars[i].prevZ = stars[i].z;
      }
    }
    // ==== UPDATE END ====

    // ==== DRAW START ====
    BeginDrawing();

    ClearBackground(BLACK);
    for (int i = 0; i < STAR_COUNT; i++) {
      // calculate the star x,y positioned around the center of the screen and
      // not the top,left
      float sx = Remap(stars[i].x / stars[i].z, 0.0F, 1.0F, 0.0F,
                       (float)SCREEN_WIDTH) +
                 CENTER_X;
      float sy = Remap(stars[i].y / stars[i].z, 0.0F, 1.0F, 0.0F,
                       (float)SCREEN_HEIGHT) +
                 CENTER_Y;

      // calculate the previous x,y position of the star
      float prevX = Remap(stars[i].x / stars[i].prevZ, 0.0F, 1.0F, 0.0F,
                          (float)SCREEN_WIDTH) +
                    CENTER_X;
      float prevY = Remap(stars[i].y / stars[i].prevZ, 0.0F, 1.0F, 0.0F,
                          (float)SCREEN_HEIGHT) +
                    CENTER_Y;

      // stars should grow in size as they get closer
      // float radius = Remap(stars[i].z, 0, SCREEN_WIDTH, MAX_RADIUS,
      // MIN_RADIUS); DrawCircle(sx, sy, radius, WHITE); stroke should change
      // based on z
      float strokeWeight =
          Remap(stars[i].z, 0.0F, (float)SCREEN_WIDTH, 5.0F, 0.0F);

      // draw streaking
      Vector2 currentPos = {sx, sy};
      Vector2 prevPos = {prevX, prevY};
      DrawLineEx(currentPos, prevPos, strokeWeight, STAR_COLOR);

      // track z values
      stars[i].prevZ = stars[i].z;
    }
    // ==== DRAW END ====

    EndDrawing();
  }

  // ===== INITIALIZATION END =====
  CloseWindow();
  return 0;
}
