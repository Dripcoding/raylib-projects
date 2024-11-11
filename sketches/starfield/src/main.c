#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int FPS = 60;
const int STAR_COUNT = 100;

typedef struct Star {
  int x;
  int y;
  int z;
} Star;

Star* initializeStars() {
  Star* stars = malloc(STAR_COUNT * sizeof(Star));

  for (int i = 0; i < STAR_COUNT; i++) {
	stars[i].x = GetRandomValue(0, SCREEN_WIDTH);
	stars[i].y = GetRandomValue(0, SCREEN_HEIGHT);
	stars[i].z = GetRandomValue(0, SCREEN_WIDTH);
  }

  return stars;
}

// todo: create static ellipsis to represent starts, centered on screen
// todo: stars should move outward from the center of the screen with a given speed
// todo: star size depends on a z value, with closer stars being larger

int main(void) {
  // ===== INITIALIZATION START =====
  SetTargetFPS(60);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starfield");

  Star* stars = initializeStars();

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
	// ==== UPDATE START ====

	// ==== UPDATE END ====

	// ==== DRAW START ====
	BeginDrawing();

	ClearBackground(BLACK);

	for (int i = 0; i < STAR_COUNT; i++) {
		DrawCircle(stars[i].x, stars[i].y, 5, WHITE);
	}

	// ==== DRAW END ====

	EndDrawing();
  }

  // ===== INITIALIZATION END =====
  CloseWindow();

  return 0;
}