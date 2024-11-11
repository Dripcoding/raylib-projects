#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const float CENTER_X = SCREEN_WIDTH / 2;
const float CENTER_Y = SCREEN_HEIGHT / 2;
const int FPS = 60;
const int STAR_COUNT = 1000;
const float SIMULATION_SPEED = 5;
const float MAX_RADIUS = 16;
const float MIN_RADIUS = 0;

typedef struct Star {
  float x;
  float y;
  float z;
};

struct Star* initializeStars() {
	struct Star* stars = malloc(STAR_COUNT * sizeof(struct Star));
	if (stars == NULL) {
		return NULL;
	}
	
	for (int i = 0; i < STAR_COUNT; i++) {
		struct Star star = {
			.x = GetRandomValue(-CENTER_X, CENTER_X),
			.y = GetRandomValue(-CENTER_Y, CENTER_Y),
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

	for (int i = 0; i < STAR_COUNT; i++) {
		stars[i].z -= SIMULATION_SPEED;

		if (stars[i].z < 1) {
			stars[i].z = SCREEN_WIDTH;
			stars[i].x = GetRandomValue(-CENTER_X, CENTER_X);
			stars[i].y = GetRandomValue(-CENTER_Y, CENTER_Y);
		}
	}
	// ==== UPDATE END ====

	// ==== DRAW START ====
	BeginDrawing();

	ClearBackground(BLACK);

	for (int i = 0; i < STAR_COUNT; i++) {
		// calculate the star x,y positioned around the center of the screen and not the top,left
		float sx = Remap(stars[i].x / stars[i].z, 0, 1, 0, SCREEN_WIDTH) + CENTER_X;
		float sy = Remap(stars[i].y / stars[i].z, 0, 1, 0, SCREEN_HEIGHT) + CENTER_Y;

		// stars should grow in size as they get closer
		float radius = Remap(stars[i].z, 0, SCREEN_WIDTH, MAX_RADIUS, MIN_RADIUS);

		DrawCircle(sx, sy, radius, WHITE);
	}
	// ==== DRAW END ====

	EndDrawing();
  }

  // ===== INITIALIZATION END =====
  CloseWindow();

  return 0;
}