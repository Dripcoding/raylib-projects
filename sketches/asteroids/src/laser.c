#include "laser.h"
#include "asteroids.h"
#include "ship.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

const float LASER_SPEED = 700.0F;
const float LASER_RADIUS = 3.0F;
const float LASER_FIRE_RATE = 0.2F;

// Laser direction constant
const Vector2 LASER_BASE_DIRECTION = {0, -1}; // Base direction pointing up

// Array management constants
const int ASTEROID_CAPACITY_INCREMENT = 10;

void initializeLasers(Laser *lasers) {
  for (int i = 0; i < MAX_LASERS; i++) {
    lasers[i].active = false;
    lasers[i].position = (Vector2){0, 0};
    lasers[i].velocity = (Vector2){0, 0};
    lasers[i].color = WHITE;
  }
}

void fireLaser(Laser *lasers, Ship *ship, int *laserCount,
               float *lastFireTime) {
  float currentTime = (float)GetTime();
  if (currentTime - *lastFireTime < LASER_FIRE_RATE) {
    return;
  }
  for (int i = 0; i < MAX_LASERS; i++) {
    if (!lasers[i].active) {
      lasers[i].active = true;

      // Calculate precise spawn position at the ship's front tip
      Vector2 shipDirection =
          Vector2Rotate(LASER_BASE_DIRECTION, ship->heading * DEG2RAD);
      Vector2 frontTipPosition =
          Vector2Add(ship->position, Vector2Scale(shipDirection, ship->radius));
      lasers[i].position = frontTipPosition;
      lasers[i].color = WHITE;

      // Calculate laser velocity: base laser speed + ship's velocity
      Vector2 laserBaseVelocity = Vector2Scale(shipDirection, LASER_SPEED);
      lasers[i].velocity = Vector2Add(laserBaseVelocity, ship->velocity);

      (*laserCount)++;
      *lastFireTime = currentTime;
      break;
    }
  }
}

void updateLasers(Laser *lasers, int screenWidth, int screenHeight) {
  for (int i = 0; i < MAX_LASERS; i++) {
    if (lasers[i].active) {
      lasers[i].position = Vector2Add(
          lasers[i].position, Vector2Scale(lasers[i].velocity, GetFrameTime()));
      if (lasers[i].position.x < -LASER_RADIUS ||
          lasers[i].position.x > (float)screenWidth + LASER_RADIUS ||
          lasers[i].position.y < -LASER_RADIUS ||
          lasers[i].position.y > (float)screenHeight + LASER_RADIUS) {
        lasers[i].active = false;
      }
    }
  }
}

void drawLasers(Laser *lasers) {
  for (int i = 0; i < MAX_LASERS; i++) {
    if (lasers[i].active) {
      DrawCircleV(lasers[i].position, LASER_RADIUS, lasers[i].color);
    }
  }
}

int checkLaserAsteroidCollisions(Laser *lasers, Asteroid **asteroids,
                                 int *asteroidCount, int *asteroidCapacity) {
  int hitCount = 0;

  for (int i = 0; i < MAX_LASERS; i++) {
    if (lasers[i].active) {
      for (int j = 0; j < *asteroidCount; j++) {
        if (!(*asteroids)[j].hit && (*asteroids)[j].radius > 0) {
          float distance =
              Vector2Distance(lasers[i].position, (*asteroids)[j].position);
          float collisionDistance = LASER_RADIUS + (*asteroids)[j].radius;

          if (distance <
              collisionDistance) { // Check if asteroid is large enough to split
            if ((*asteroids)[j].radius > ASTEROID_SPLIT_THRESHOLD) {
              // Ensure we have space for 2 more asteroids
              if (*asteroidCount + 2 > *asteroidCapacity) {
                *asteroidCapacity =
                    *asteroidCount + ASTEROID_CAPACITY_INCREMENT;
                *asteroids =
                    realloc(*asteroids, sizeof(Asteroid) * (*asteroidCapacity));
                if (*asteroids == NULL) {
                  printf("Failed to reallocate asteroid array\n");
                  return hitCount;
                }
              }

              // Split the asteroid
              Asteroid *newAsteroids = splitAsteroid(&(*asteroids)[j]);
              if (newAsteroids != NULL) {
                // Add both new asteroids to the end
                (*asteroids)[*asteroidCount] = newAsteroids[0];
                (*asteroids)[*asteroidCount + 1] = newAsteroids[1];
                *asteroidCount += 2;
                free(newAsteroids);
              }
            }

            // Remove the hit asteroid
            (*asteroids)[j].hit = true;
            (*asteroids)[j].radius = 0;
            lasers[i].active = false;
            hitCount++;
          }
        }
      }
    }
  }

  return hitCount;
}
