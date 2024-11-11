#include "raylib.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int CENTER_X = SCREEN_WIDTH / 2;
const int CENTER_Y = SCREEN_HEIGHT / 2;
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
	stars[i].x = GetRandomValue(CENTER_X, SCREEN_WIDTH);
	stars[i].y = GetRandomValue(CENTER_Y, SCREEN_HEIGHT);
	stars[i].z = SCREEN_WIDTH;
  }

  return stars;
}

// todo: star size depends on a z value, with closer stars being larger

int main(void) {
  // ===== INITIALIZATION START =====
  SetTargetFPS(60);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starfield");

  Star* stars = initializeStars();

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
	// ==== UPDATE START ====
	// todo: stars should move outward from the center of the screen with a given speed

	float sx;
	float sy;

	for (int i = 0; i < STAR_COUNT; i++) {
		if (stars[i].z != 0) {
			stars[i].z = stars[i].z - 1;
			// stars[i].x = stars[i].x + 5;
			// stars[i].y = stars[i].y + 5;
		}
	}

	// ==== UPDATE END ====

	// ==== DRAW START ====
	BeginDrawing();

	ClearBackground(BLACK);

	for (int i = 0; i < STAR_COUNT; i++) {
		if (stars[i].z != 0) {
			DrawCircle(stars[i].x, stars[i].y, 5, WHITE);
		}
	}

	// ==== DRAW END ====

	EndDrawing();
  }

  // ===== INITIALIZATION END =====
  CloseWindow();

  return 0;
}