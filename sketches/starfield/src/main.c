#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float CENTER_X = SCREEN_WIDTH / 2;
const float CENTER_Y = SCREEN_HEIGHT / 2;
const int FPS = 60;
const int STAR_COUNT = 500;

typedef struct Star {
  float x;
  float y;
  float z;
};

struct Star* initializeStars() {
	struct Star* stars = malloc(STAR_COUNT * sizeof(struct Star));
	if (stars == NULL) {
		return NULL; // Return NULL if memory allocation fails
	}

	for (int i = 0; i < STAR_COUNT; i++) {
		struct Star star = {
			.x = GetRandomValue(0, SCREEN_WIDTH),
			.y = GetRandomValue(0, SCREEN_HEIGHT),
			.z = GetRandomValue(0, SCREEN_WIDTH)
		};

		stars[i] = star;
	}
	
	return stars;
}

// todo: star size depends on a z value, with closer stars being larger

int main(void) {
  // ===== INITIALIZATION START =====
  SetTargetFPS(60);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starfield");
  struct Star* stars = initializeStars();

  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
	// ==== UPDATE START ====
	// todo: stars should move outward from the center of the screen with a given speed

	for (int i = 0; i < STAR_COUNT; i++) {
		stars[i].z -= 1; // simulation speed

		// if (stars[i].z <= 0) {
		// 	stars[i].z = SCREEN_WIDTH;
		// }
	}
	// ==== UPDATE END ====

	// ==== DRAW START ====
	BeginDrawing();

	ClearBackground(BLACK);

	for (int i = 0; i < STAR_COUNT; i++) {
		
		float sx = Remap(stars[i].x / stars[i].z, 0, 1, 0, SCREEN_WIDTH);
		float sy = Remap(stars[i].y / stars[i].z, 0, 1, 0, SCREEN_HEIGHT);

		DrawCircle(sx, sy, 5, WHITE);
	}
	// ==== DRAW END ====

	EndDrawing();
  }

  // ===== INITIALIZATION END =====
  CloseWindow();

  return 0;
}