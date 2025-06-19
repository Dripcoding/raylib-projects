#include "asteroids.h"
#include "laser.h"
#include "raylib.h"
#include "ship.h"
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main(void) {
  // ===== INITIALIZATION START =====

  SetTargetFPS(60);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

  // Initialize ship
  Ship *ship = initializeShip(
      (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2});
  if (ship == NULL) {
    printf("Failed to initialize ship\n");
    CloseWindow();
    return -1;
  }

  // Initialize asteroids
  Asteroid *asteroids = initializeAsteroids(SCREEN_WIDTH, SCREEN_HEIGHT);
  if (asteroids == NULL) {
    printf("Failed to initialize asteroids\n");
    free(ship);
    CloseWindow();
    return -1;
  }

  // Dynamic asteroid array tracking
  int asteroidCount = MAX_ASTEROID_COUNT;
  int asteroidCapacity = MAX_ASTEROID_COUNT;

  // Initialize lasers
  Laser lasers[MAX_LASERS];
  int currentLaserCount = 0;
  float lastFireTime = 0.0F;
  initializeLasers(lasers);

  // Initialize game state
  bool gameOver = false;
  int hitAsteroids = 0;

  // ===== INITIALIZATION END =====
  // ===== GAME LOOP START =====
  while (!WindowShouldClose()) {
    printf("Asteroids hit: %d\n", hitAsteroids);

    // ===== UPDATE START =====
    if (!gameOver) {
      // Only update game if not in game over state
      if (ship->isBoosting) {
        boostShip(ship);
      }

      wrapShip(ship, SCREEN_WIDTH, SCREEN_HEIGHT);

      ship->position = Vector2Add(ship->position, ship->velocity);

      if (IsKeyDown(KEY_RIGHT)) {
        rotateShip(ship, KEY_RIGHT);
      }
      if (IsKeyDown(KEY_LEFT)) {
        rotateShip(ship, KEY_LEFT);
      }
      if (IsKeyDown(KEY_UP)) {
        ship->isBoosting = true;
        boostShip(ship);
      }
      if (IsKeyReleased(KEY_UP)) {
        ship->isBoosting = false;
      }
      if (IsKeyDown(KEY_SPACE)) {
        fireLaser(lasers, ship, &currentLaserCount, &lastFireTime);
      }
      updateAsteroids(asteroids, asteroidCount, SCREEN_WIDTH, SCREEN_HEIGHT);
      updateLasers(lasers, SCREEN_WIDTH, SCREEN_HEIGHT);

      // Check for collision between lasers and asteroids
      hitAsteroids += checkLaserAsteroidCollisions(
          lasers, &asteroids, &asteroidCount, &asteroidCapacity);

      // Check for collision between ship and asteroids
      gameOver = checkShipAsteroidCollision(ship, asteroids, asteroidCount);
    }

    if (gameOver && IsKeyPressed(KEY_ENTER)) {
      // Reset game state
      gameOver = false;
      hitAsteroids = 0;

      // Reset ship
      ship->position =
          (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};
      ship->velocity = (Vector2){0, 0};
      ship->heading = 0;
      ship->isBoosting = false;

      // Reset asteroids
      free(asteroids);
      asteroids = initializeAsteroids(SCREEN_WIDTH, SCREEN_HEIGHT);
      asteroidCount = MAX_ASTEROID_COUNT;
      asteroidCapacity = MAX_ASTEROID_COUNT;

      // Reset lasers
      initializeLasers(lasers);
      currentLaserCount = 0;
      lastFireTime = 0.0F;
    }

    // ===== UPDATE END =====

    // ===== DRAWING START =====
    BeginDrawing();

    if (!gameOver) {
      // Normal game drawing
      ClearBackground(BLACK);
      drawAsteroids(asteroids, asteroidCount);
      drawLasers(lasers);
      DrawPolyLines(ship->position, 3, ship->radius, ship->heading,
                    ship->color);

      // Draw hit asteroids count in top left
      DrawText(TextFormat("Score: %d", hitAsteroids), 10, 10, 20, WHITE);
    } else {
      // Game over screen
      ClearBackground(BLUE);

      // Draw game over message
      int screenCenterX = SCREEN_WIDTH / 2;
      int screenCenterY = SCREEN_HEIGHT / 2;

      DrawText("GAME OVER", screenCenterX - 120, screenCenterY - 60, 50, WHITE);
      DrawText(TextFormat("Final Score: %d", hitAsteroids), screenCenterX - 80,
               screenCenterY - 10, 20, WHITE);
      DrawText("Press ENTER to restart", screenCenterX - 90, screenCenterY + 20,
               20, WHITE);
      DrawText("Press ESC to exit", screenCenterX - 70, screenCenterY + 50, 20,
               WHITE);
    }

    EndDrawing();
    // ===== DRAWING END =====
  }
  // ===== GAME LOOP END =====

  // Clean up memory
  free(ship);
  free(asteroids);
  CloseWindow();
  return 0;
}
