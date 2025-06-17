#include "laser.h"
#include "asteroids.h"
#include "ship.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

const float LASER_SPEED = 700.0F;
const float LASER_RADIUS = 3.0F;
const float LASER_FIRE_RATE = 0.2F;

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

      // Calculate offset relative to ship's direction
      Vector2 baseOffset = {-10.0F, -20.0F};
      Vector2 rotatedOffset =
          Vector2Rotate(baseOffset, (ship->heading * DEG2RAD));
      Vector2 offsetPosition = Vector2Add(ship->position, rotatedOffset);
      lasers[i].position = offsetPosition;
      lasers[i].color = WHITE;

      // Calculate laser velocity: base laser speed + ship's velocity
      Vector2 direction = {0, -1}; // Base direction pointing up
      Vector2 laserDirection =
          Vector2Rotate(direction, ship->heading * DEG2RAD);
      Vector2 laserBaseVelocity = Vector2Scale(laserDirection, LASER_SPEED);
      lasers[i].velocity = Vector2Add(laserBaseVelocity, ship->velocity);

      // Debug: Print ship velocity to see if it's being applied
      printf("Ship velocity: (%.2f, %.2f), Laser velocity: (%.2f, %.2f)\n",
             ship->velocity.x, ship->velocity.y, lasers[i].velocity.x,
             lasers[i].velocity.y);

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

int checkLaserAsteroidCollisions(Laser *lasers, Asteroid *asteroids) {
  int hitCount = 0;

  for (int i = 0; i < MAX_LASERS; i++) {
    if (lasers[i].active) {
      for (int j = 0; j < MAX_ASTEROID_COUNT; j++) {
        if (!asteroids[j].hit && asteroids[j].radius > 0) {
          float distance =
              Vector2Distance(lasers[i].position, asteroids[j].position);
          float collisionDistance = LASER_RADIUS + asteroids[j].radius;

          if (distance < collisionDistance) {
            asteroids[j].hit = true;
            lasers[i].active = false;
            hitCount++;
          }
        }
      }
    }
  }

  return hitCount;
}
