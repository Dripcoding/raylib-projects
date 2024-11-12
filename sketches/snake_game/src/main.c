#include "raylib.h"
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SNAKE_SPEED = 5;

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

void updateSnake(struct Snake* snake) {
	int key = GetKeyPressed();

	// snake movement with arrow keys
	if (IsKeyDown(KEY_RIGHT)) snake -> position.x += snake -> speed.x;
	if (IsKeyDown(KEY_LEFT)) snake -> position.x -= snake -> speed.x;
	if (IsKeyDown(KEY_UP)) snake -> position.y -= snake -> speed.y;
	if (IsKeyDown(KEY_DOWN)) snake -> position.y += snake -> speed.y;
}

int main(void) {
	// ===== INITIALIZATION START =====
	SetTargetFPS(60);
  	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");

	struct Snake snake = {
		.position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
		.size = {20, 20},
		.speed = {SNAKE_SPEED, SNAKE_SPEED},
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

		updateSnake(&snake);

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