#include "raylib.h"
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

// todo: create and initialize the snake with 1 segment
// todo: create and initialize the food (1 to start with)
// todo: use keyboard controls to move the snake and change direction
// todo: detect collision between the snake and the food
// todo: detect collision between the snake and the screen
// todo: create and initialize the score
// todo: create and initialize the game over message

typedef struct Snake {
	Vector2 position;
	Vector2 speed;
	Vector2 size;
	Color color;
};

typedef struct Food {
	Vector2 position;
	Vector2 size;
	Color color;
};

int main(void) {
	// ===== INITIALIZATION START =====
	SetTargetFPS(60);
  	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");

	struct Snake snake = {
		.position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
		.size = {20, 20},
		.speed = {0, 0},
		.color = MAROON,
	};

	struct Food food = {
		.position = {GetRandomValue(0, SCREEN_WIDTH), GetRandomValue(0, SCREEN_HEIGHT)},
		.size = {20, 20},
		.color = GREEN,
	};
	// ===== INITIALIZATION END =====

	// ===== GAME LOOP START =====
	while (!WindowShouldClose()) {
		// ===== UPDATE START =====

		// ===== UPDATE END =====

		// ===== DRAW START =====
		BeginDrawing();

		ClearBackground(BLACK);

		DrawRectangleV(snake.position, snake.size, snake.color);		
		DrawRectangleV(food.position, food.size, food.color);

		EndDrawing();
		// ===== DRAW END =====
	}

	// ===== GAME LOOP END =====
	CloseWindow();
	
	return 0;
}