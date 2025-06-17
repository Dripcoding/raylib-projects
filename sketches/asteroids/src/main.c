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

    updateAsteroids(asteroids, SCREEN_WIDTH, SCREEN_HEIGHT);
    updateLasers(lasers, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Check for collision between lasers and asteroids
    hitAsteroids += checkLaserAsteroidCollisions(lasers, asteroids);

    // Check for collision between ship and asteroids
    gameOver = checkShipAsteroidCollision(ship, asteroids);

    // ===== UPDATE END =====    // ===== DRAWING START =====
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw game objects only if game is not over
    drawAsteroids(asteroids);
    drawLasers(lasers);
    DrawPolyLines(ship->position, 3, ship->radius, ship->heading, ship->color);

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
