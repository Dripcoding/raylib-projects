#include "raylib.h"
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// todo: create and initialize the snake with 1 segment
// todo: create and initialize the food (1 to start with)
// todo: detect collision between the snake and the food
// todo: detect collision between the snake and the screen
// todo: create and initialize the score
// todo: create and initialize the game over message

int main(void) {
	// ===== INITIALIZATION START =====
	SetTargetFPS(60);
  	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
	// ===== INITIALIZATION END =====

	// ===== GAME LOOP START =====
	while (!WindowShouldClose()) {
		// ===== UPDATE START =====

		// ===== UPDATE END =====

		// ===== DRAW START =====
		BeginDrawing();
		
		EndDrawing();
		// ===== DRAW END =====
	}

	// ===== GAME LOOP END =====
	CloseWindow();
	
	return 0;
}