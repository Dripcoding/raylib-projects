#include "raylib.h"

const SCREEN_WIDTH = 1920;
const SCREEN_HEIGHT = 1080;
const FPS = 60;

int main(void) {
  // ===== INITIALIZATION START =====
  SetTargetFPS(60);

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Starfield");


  // ===== MAIN LOOP =====
  while (!WindowShouldClose()) {
	// ==== UPDATE START ====

	// ==== UPDATE END ====

	// ==== DRAW START ====
	BeginDrawing();

	ClearBackground(BLACK);

	// ==== DRAW END ====

	EndDrawing();
  }

  // ===== INITIALIZATION END =====
  CloseWindow();

  return 0;
}